#ifndef SYS_CALL_H
#define SYS_CALL_H

#include "headers.h"

typedef struct Node{
    pid_t pid;
    char* process;
    struct Node* next;
}Node;

Node* LinkedList();
Node* insert_node(Node* head , pid_t pid , char*process);
Node* _delete(Node* head);

void syst_call(char **args, int num_args,char*command , Node*head , int*time , int background);



#endif