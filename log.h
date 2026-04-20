#ifndef __LOG_H
#define __LOG_H

#include "headers.h"

// Queue functions

typedef struct Queue{
    int front ; 
    int rear;
    char**array ;
    int count ;
    int size;
}Queue;

Queue* createQueue(int size);
bool isFull(Queue* q);
bool isEmpty(Queue* q);
Queue* enqueue(Queue* q , char* string);
Queue* dequeue(Queue* q);
void freeQueue(Queue* q);
char* peek_front(Queue* q);
char* peek_rear(Queue* q);

void log_f(char** args , int num_args , Queue*Q , char* root , char* previous_directory , Node*head, int*time , char*command);



#endif