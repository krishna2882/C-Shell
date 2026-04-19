#include "headers.h"



void display(char* root_dir_buffer, int size_root_dir_buffer , int*time , char*func){
    char* username = getlogin();
    if (username==NULL)
    {
        perror("Cannot figure out username");
        exit(EXIT_FAILURE);
    }
    char system_name[4096];
    if (system_name==NULL)
    {
        perror("Cannot figure out system name");
        exit(EXIT_FAILURE);
    }
    
    if (gethostname(system_name, sizeof(system_name))!=0)
    {
        perror("Cannot figure out system name");
        exit(EXIT_FAILURE);
    }
    char current_working_dir[4096];
    char* current_dir = getcwd(current_working_dir, sizeof(current_working_dir));
    
    if (strncmp(root_dir_buffer, current_dir, size_root_dir_buffer) == 0) {
        printf("<%s@%s:~", username, system_name);
        printf("%s", current_working_dir + size_root_dir_buffer);
    }
    else
    {
        printf("<%s@%s:%s", username, system_name, current_working_dir);
    }

    if(*time>=2)
    {
        printf(": %s: %d>",func , *time);
    }
    else{
        printf(">");
    }
    
}