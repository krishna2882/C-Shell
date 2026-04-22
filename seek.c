#include "headers.h"

void recursive(int d, int f, char *path, char *target_name, int *count, char *path_e)
{
    struct dirent **list;
    int n = scandir(path, &list, NULL, alphasort);

    for (int i = 0; i < n; ++i)
    {
        struct dirent *entry = list[i];
        if (entry->d_name[0] == '.')
            continue;

        char full_path[4097];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat file_stat;
        if (stat(full_path, &file_stat) == -1)
            continue;
        bool is_target = strncmp(target_name, entry->d_name, strlen(target_name)) == 0;
        bool is_dir = S_ISDIR(file_stat.st_mode);
        bool is_file = S_ISREG(file_stat.st_mode);
        bool has_extension = entry->d_name[strlen(target_name)] == '.';
        bool exact_match = entry->d_name[strlen(target_name)] == '\0';

        if (is_target && ((d && is_dir) || (f && is_file && has_extension) || (!d && !f && (has_extension || exact_match))))
        {
            (*count)++;
            if (is_dir)
                printf("\033[34m%s\n\033[0m", full_path);
            else if (is_file)
                printf("\033[32m%s\n\033[0m", full_path);

            strcpy(path_e, full_path);
        }
        if (is_dir)
            recursive(d, f, full_path, target_name, count, path_e);
    }

}


void seek(char** args , int num_args , char* root , char* previous_directory) {
    int d=0 , f=0  , e=0 ;
    int count =0 ;
    for(int i=0 ; i<num_args ; i++){
        if(args[i][0]=='-'){
            if(strcmp(args[i] , "-d")==0){
                d=1;
            }
            else if(strcmp(args[i] , "-f")==0){
                f=1;
            }
            else if(strcmp(args[i] , "-e")==0){
                e=1;
            }
        }
        else{
            if(d==1 && f==1){
                printf("Invalid flags\n");
                return;
            }
            char present_directory[4097];
            getcwd(present_directory ,sizeof(present_directory));
            char* target_path = (char*)malloc(4097*sizeof(char));
            if(i+1 == num_args)
            {
                strcpy(target_path , present_directory);
            }
            else if(args[i+1][0] == '~')
            {
                snprintf(target_path , sizeof(target_path) , "%s%s" , root , args[i+1]+1);
            }
            else{
                strcpy(target_path , args[i+1]);
            }
            // printf("%s\n" , target_path);
            int check = chdir(target_path);
            if(check!=0)
            {
                perror("chdir");
                return;
            }
            char* final_directory = ".";
            char path_e[4097];
            recursive(d,f,final_directory , args[i] , &count , path_e);
            if(count == 0)
            {
                printf("No match found!\n");
                check = chdir(present_directory);
                if(check!=0)
                {
                    perror("chdir");
                    return;
                }
                return ;
            }
            int t = 0;
            if (e == 1)
            {
                if (count == 1)
                {
                    struct stat file_stat;
                    if (stat(path_e, &file_stat) == -1)
                    {
                        continue;
                    }
                    DIR *directory = opendir(path_e);
                    if (directory)
                    {
                        t = 1;
                        if (chdir(path_e) != 0)
                        {
                            perror("chdir");
                            closedir(directory);
                            return;
                        }
                        closedir(directory);
                    }
                    else if (S_ISREG(file_stat.st_mode))
                    {
                        FILE *file = fopen(path_e, "r");
                        if (!file)
                        {
                            perror("fopen");
                            return;
                        }

                        char buffer[1024];
                        size_t b_read;

                        while ((b_read = fread(buffer, 1, sizeof(buffer), file)) > 0)
                        {

                            fwrite(buffer, 1, b_read, stdout);
                        }

                        fclose(file);
                    }
                }
                else if (count == 0)
                {
                    printf("No match found!\n");
                }
            }
            if (t == 0)
            {
                if (chdir(present_directory) != 0)
                {
                    perror("chdir");
                    return;
                }
            }
        }
    }
}