#include "headers.h"

void proc_f(int pid, char *root)
{
    char executable_path[4097], final_exe[4097];
    snprintf(executable_path, sizeof(executable_path), "/proc/%d/exe", pid);
    ssize_t n_bytes = readlink(executable_path, final_exe, sizeof(final_exe));

    if (n_bytes != -1)
    {
        if (strncmp(root, final_exe, strlen(root)) == 0)
        {
            final_exe[0] = '~';
            memmove(&final_exe[1], &final_exe[strlen(root)], n_bytes - strlen(root));
            final_exe[n_bytes - strlen(root) + 1] = '\0';
        }
    }
    else
    {
        printf("Error in reading the executable path\n");
        return;
    }
    char stat_path[4097];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", pid);
    FILE *fid = fopen(stat_path, "r");
    if (!fid)
    {
        printf("Error opening stat file\n");
        return;
    }
    char stat_file[4097];
    if (!fgets(stat_file, sizeof(stat_file), fid))
    {
        printf("Error reading stat file\n");
        fclose(fid);
        return;
    }
    fclose(fid);

    char *token;
    int vm_size = 0, pgrp = 0, tpgid = 0;
    char status = '\0', fg_bg = '-';

    token = strtok(stat_file, " ");
    for (int i = 0; token != NULL; ++i)
    {
        switch (i)
        {
        case 2:
            status = token[0];
            break;
        case 4:
            pgrp = atoi(token);
            break;
        case 7:
            tpgid = atoi(token);
            break;
        case 22:
            vm_size = atoi(token) / 1024; // Convert to KB
            break;
        }
        token = strtok(NULL, " ");
    }
    fg_bg = (pgrp == tpgid) ? '+' : '-';

    printf("PID : %d\n", pid);
    printf("Process Status : %c%c\n", status, fg_bg);
    printf("Process Group : %d\n", pgrp);
    printf("Virtual Memory : %d KB\n", vm_size);
    printf("Executable Path : %s\n", final_exe);
}


void proclore(char** args , int num_args , char*root)
{
    if(num_args == 0)
    {
        int pid = getpid();
        proc_f(pid , root);
    }
    else{
        int pid = atoi(args[0]);
        proc_f(pid , root);
    }
}
