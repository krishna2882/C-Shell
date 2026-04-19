#include "headers.h"

void hop(char *path, char* root_dir_buffer , char* previous_directory) {
    char current_working_directory[5000];
    char target_path[5000];
    getcwd(current_working_directory, sizeof(current_working_directory));

    if (path[0] == '~') {
        snprintf(target_path, sizeof(target_path), "%s%s", root_dir_buffer, path + 1);
    }
    else if (strcmp(path, "-") == 0) {
        if (strlen(previous_directory) == 0) {
            printf("OLDPWD not set\n");
            return;
        }
        if (chdir(previous_directory) != 0) {
            perror("Error changing directory to previous");
            return;
        }
        strcpy(target_path, previous_directory);
    } else{
        strcpy(target_path, path);
    }
    if (chdir(target_path) != 0) {
        perror("Error changing directory");
        return;
    }
    strcpy(previous_directory, current_working_directory);
    getcwd(current_working_directory, sizeof(current_working_directory));
    printf("%s\n", current_working_directory);
}

void execute_hop(char **args, int num_args, char* root_dir_buffer, char* previous_directory) {
    if (num_args<1)
    {
        perror("No flag provided!\n");
        return;
    }
    for (int i = 0; i < num_args; i++) {
        hop(args[i], root_dir_buffer , previous_directory);
    }
}
