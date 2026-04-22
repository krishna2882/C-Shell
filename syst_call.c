#include "headers.h"

Node*LinkedList()
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->next = NULL;
    n->process = NULL;
    return n;
}

Node* insert_node(Node* head , pid_t pid , char*process)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->pid = pid;
    new_node->process = process;
    new_node->next = head->next;
    head->next = new_node;
    return head;
}

Node* delete_node(Node* prev, Node* current) {
    Node* next_node = current->next;
    prev->next = next_node;
    free(current);
    return next_node;
}

Node* _delete(Node* head) {
    Node* prev = head;
    if(head==NULL)
    {
        return head;
    }
    Node* current = head->next;

    while (current != NULL) {
        int status;
        int check = waitpid(current->pid, &status, WNOHANG);
        int t = WIFEXITED(status);
        if (check == current->pid) {
            if (t) {
                printf("%s Exited Normally (%d)\n", current->process, current->pid);
            } else {
                printf("%s Exited Abnormally (%d)\n", current->process, current->pid);
            }
            current = delete_node(prev, current);
        } else {
            prev = current;
            current = current->next;
        }
    }

    return head;
}


void syst_call(char **args, int num_args,char*command , Node*head , int*time , int background)
{
    char*command_name = args[0];
    char command_name_copy[5000];
    strcpy(command_name_copy , command_name);
    struct timespec start_time , end_time ;
    args[num_args] = NULL;
    pid_t pid = fork();
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    if(pid<0)
    {
        perror("Error in fork") ;
    }
    else if(pid==0)
    {
        execvp(command_name,args);
        printf("No such command found\n");
        return ;
    }
    else{
         if(background==0)
        {
            int status;
            double cpu_used;
            pid_t terminated_child_pid = waitpid(pid, &status, 0);
            clock_gettime(CLOCK_MONOTONIC, &end_time);  
            // printf("%d\n" , pid);
            int elapsed_time = (end_time.tv_sec - start_time.tv_sec);
            int t = (int)elapsed_time;
            if(t>=2)
            {
                strcpy(command , command_name_copy);
                (*time) = t ;
            }
        }
        else{
            printf("%d\n" , pid);
            head = insert_node(head , pid ,command_name_copy );
        }
    }
    
}