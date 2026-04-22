#include "headers.h"

char* get_new_directory(char* path , char* root_dir_buffer , char* previous_directory)
{
    char* target_path = (char*)malloc(5000*sizeof(char));
    if (path[0] == '~') {
        snprintf(target_path, sizeof(target_path), "%s%s", root_dir_buffer, path + 1);
    }
    else if (strcmp(path, "-") == 0) {
        if (strlen(previous_directory) == 0) {
            printf("OLDPWD not set\n");
            return NULL;
        }
        strcpy(target_path, previous_directory);
    } else{
        strcpy(target_path, path);
    }
    return target_path;
}

void function_reveal(int a , int l)
{
    char present_directory[5000];
    getcwd(present_directory , sizeof(present_directory));
    struct dirent **list;
    int num = scandir(present_directory, &list, NULL, alphasort);
    if (num <0)
    {
        perror("scandir");
    }
    if(l==0)
    {
        for(int i=0 ; i<num ; i++)
        {
            if(num ==0 )
            {
                break ;
            }
            struct stat file_stat;
            char path[6096];
            snprintf(path , sizeof(path) , "%s/%s" , present_directory , list[i]->d_name);
            int t = stat(path , &file_stat);
            if(t == -1)
            {
                perror("opendir");
                break;
            }
            if(a==1)
            {
                const char *file_name = list[i]->d_name;
                if (S_ISDIR(file_stat.st_mode)) {
                    printf("\033[34m%s\033[0m", file_name);
                } else if (file_stat.st_mode & S_IXUSR) {
                    printf("\033[32m%s\033[0m", file_name);
                } else {
                    printf("%s", file_name);
                }
                printf("\n");
            }
            else{
                if(list[i]->d_name[0]!='.')
                {
                    const char *file_name = list[i]->d_name;
                    if (S_ISDIR(file_stat.st_mode)) {
                        printf("\033[34m%s\033[0m", file_name);
                    } else if (file_stat.st_mode & S_IXUSR) {
                        printf("\033[32m%s\033[0m", file_name);
                    } else {
                        printf("%s", file_name);
                    }
                    printf("\n");
                }
            }
             
        }
    }
    else{
        for(int i=0 ; i<num ; i++)
        {
            if(num ==0 )
            {
                break ;
            }
            struct stat file_stat;
            char path[6096];
            snprintf(path , sizeof(path) , "%s/%s" , present_directory , list[i]->d_name);
            int t = stat(path , &file_stat);
            if(t == -1)
            {
                perror("opendir");
                break;
            }
            if(a==1)
            {
                char file_type = S_ISDIR(file_stat.st_mode) ? 'd' : '-';
                char user_read = file_stat.st_mode & S_IRUSR ? 'r' : '-';
                char user_write = file_stat.st_mode & S_IWUSR ? 'w' : '-';
                char user_exec = file_stat.st_mode & S_IXUSR ? 'x' : '-';
                char group_read = file_stat.st_mode & S_IRGRP ? 'r' : '-';
                char group_write = file_stat.st_mode & S_IWGRP ? 'w' : '-';
                char group_exec = file_stat.st_mode & S_IXGRP ? 'x' : '-';
                char others_read = file_stat.st_mode & S_IROTH ? 'r' : '-';
                char others_write = file_stat.st_mode & S_IWOTH ? 'w' : '-';
                char others_exec = file_stat.st_mode & S_IXOTH ? 'x' : '-';

                printf("%c%c%c%c%c%c%c%c%c%c", file_type, user_read, user_write, user_exec, group_read, group_write, group_exec, others_read, others_write, others_exec);

                struct passwd *user = getpwuid(file_stat.st_uid);
                struct group *group = getgrgid(file_stat.st_gid);
                char time_str[30];
                strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));

                printf(" %2lu %8s %8s %8ld ", (unsigned long)file_stat.st_nlink,
                    user ? user->pw_name : "",
                    group ? group->gr_name : "",
                    (long)file_stat.st_size);

                printf("%s \t", time_str);

                const char *file_name = list[i]->d_name;
                if (S_ISDIR(file_stat.st_mode)) {
                    printf("\033[34m%s\033[0m", file_name);
                } else if (file_stat.st_mode & S_IXUSR) {
                    printf("\033[32m%s\033[0m", file_name);
                } else {
                    printf("%s", file_name);
                }

                printf("\n");
            }
            else{
                if (list[i]->d_name[0] != '.')
                {
                    char file_type = S_ISDIR(file_stat.st_mode) ? 'd' : '-';
                    char user_read = file_stat.st_mode & S_IRUSR ? 'r' : '-';
                    char user_write = file_stat.st_mode & S_IWUSR ? 'w' : '-';
                    char user_exec = file_stat.st_mode & S_IXUSR ? 'x' : '-';
                    char group_read = file_stat.st_mode & S_IRGRP ? 'r' : '-';
                    char group_write = file_stat.st_mode & S_IWGRP ? 'w' : '-';
                    char group_exec = file_stat.st_mode & S_IXGRP ? 'x' : '-';
                    char others_read = file_stat.st_mode & S_IROTH ? 'r' : '-';
                    char others_write = file_stat.st_mode & S_IWOTH ? 'w' : '-';
                    char others_exec = file_stat.st_mode & S_IXOTH ? 'x' : '-';

                    printf("%c%c%c%c%c%c%c%c%c%c", file_type, user_read, user_write, user_exec, group_read, group_write, group_exec, others_read, others_write, others_exec);

                    struct passwd *user = getpwuid(file_stat.st_uid);
                    struct group *group = getgrgid(file_stat.st_gid);
                    char time_str[30];
                    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));

                    printf(" %2lu %8s %8s %8ld ", (unsigned long)file_stat.st_nlink,
                        user ? user->pw_name : "",
                        group ? group->gr_name : "",
                        (long)file_stat.st_size);

                    printf("%s \t", time_str);

                    const char *file_name = list[i]->d_name;
                    if (S_ISDIR(file_stat.st_mode)) {
                        printf("\033[34m%s\033[0m", file_name);
                    } else if (file_stat.st_mode & S_IXUSR) {
                        printf("\033[32m%s\033[0m", file_name);
                    } else {
                        printf("%s", file_name);
                    }

                    printf("\n");
                }
            }
        }
    }
    
}

void reveal(char**args , int num_args , char*root , char* previous_directory)
{
    int flag =0 ;
    int a = 0 , l=0 ;
    for(int i=0 ; i<num_args ; i++)
    {
        if(args[i][0]=='-')
        {
            // if(strstr(args[i] , "a")==0)
            // {
            //     a = 1;
            // }
            // else if(strstr(args[i] , "l")==0)
            // {
            //     l = 1;
            // }
            // else if(strcmp(args[i] , "-al")==0 || strcmp(args[i] , "-la")==0)
            // {
            //     a = 1;
            //     l = 1;
            // }
            int c = 1;
            while(c<strlen(args[i])){

                if(args[i][c] == 'a'){
                    a = 1;
                }
                else if(args[i][c] == 'l'){
                    l=1;
                }
                else{
                    printf("Invalid flags!\n");
                    return;
                }
                c++;
            }
        }
        else{
            flag = 1;
            char present_directory[4097];
            getcwd(present_directory ,sizeof(present_directory));
            char* target_path = get_new_directory(args[i] , root , previous_directory);
            int check = chdir(target_path);
            if(check!=0)
            {
                perror("Error changing directory");
            }
            DIR*directory = opendir(target_path);
            if(directory==NULL)
            {
                printf("No such directory exists.\n");
                return;
            }
            function_reveal(a,l);
            check = chdir(present_directory);
            if(check != 0)
            {
                printf("Unable to change the directory\n");
            }
        }
    }
    if(flag==0)
    {
        char present_directory[4097];
        getcwd(present_directory ,sizeof(present_directory));
        DIR*directory = opendir(present_directory);
        if(directory==NULL)
        {
            printf("No such directory exists.\n");
            return;
        }
        function_reveal(a,l);
    }
}
