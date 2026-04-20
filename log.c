#include "headers.h"


Queue* createQueue(int size)
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    q->size = size;
    q->array = (char**)malloc((q->size+1) * sizeof(char*));
    return q;
}

bool isFull(Queue* q)
{
    return q->count == q->size;
}

bool isEmpty(Queue* q)
{
    return q->count == 0;
}

Queue* enqueue(Queue* q , char* string)
{
    q->rear = (q->rear+1) % q->size;
    q->array[q->rear] = strdup(string);
    q->count++;
    return q;
}

Queue* dequeue(Queue* q)
{
    q->front = (q->front+1) % q->size;
    q->count--;
    return q;
}

void freeQueue(Queue* q)
{
    free(q->array);
    free(q);
}

char* peek_front(Queue* q)
{
    if(isEmpty(q))
    {
        return "Queue is empty";
    }
    return strdup(q->array[q->front]);
}

char* peek_rear(Queue* q)
{
    if(isEmpty(q))
    {
        return "Queue is empty";
    }
    return strdup(q->array[q->rear]);
}

void printQueue(Queue* q)
{
    for(int i=q->front ; i<=q->rear ; i++)
    {
        printf("%s\n" , q->array[i]);
    }
}

void log_f(char** args , int num_args , Queue*Q , char* root , char* previous_directory , Node*head, int*time , char*command)
{
    if(num_args==0)
    {
        printQueue(Q);
        return;
    }
    if(strcmp(args[0] , "purge")==0)
    {
        while(!isEmpty(Q))
        {
            Q = dequeue(Q);
        }
        return;
    }
    else if(strcmp(args[0] , "execute") == 0)
    {
        if(num_args<2)
        {
            printf("Invalid number of arguments\n");
            return;
        }
        int index = atoi(args[1]);
        int value = Q->rear +1 - index;
        if(value<0)
        {
            printf("Less than %d commands in the log\n" , index);
            return;
        }
        if(value>15)
        {
            printf("More than 15 commands are not stored in log\n");
            return;
        }
        char* event =strdup(Q->array[value]);
        char*rem_semi = strdup(event);
        int background = 0;
        while(rem_semi!=NULL)
        {
            char*tok_semi = strtok_r(rem_semi , ";\n" , &rem_semi);
            if(tok_semi==NULL)
            {
                break;
            }
            while(tok_semi!=NULL)
            {
                char token_remember[4097] ;
                strcpy(token_remember , tok_semi); 
                char*tok_and = strtok_r(tok_semi , "&" , &tok_semi);
                if(tok_and==NULL)
                {
                    break;
                }
                background = (strcmp(tok_and,token_remember ) == 0) ? 0 : 1;
                char* remaining_token = tok_and;
                char *args[100];
                int num_args = 0;
                char *token = strtok(remaining_token, " \n");
                while (token != NULL) {
                    args[num_args++] = token;
                    token = strtok(NULL, " \n");
                }

                if (num_args > 0 && strcmp(args[0], "hop") == 0) {
                    execute_hop(args + 1, num_args - 1 , root , previous_directory);
                }
                else if (num_args > 0 && strcmp(args[0], "reveal") == 0) {
                    reveal(args + 1, num_args - 1 , root , previous_directory);
                }
                else if (num_args > 0 && strcmp(args[0], "seek") == 0) {
                    seek(args + 1, num_args - 1 , root , previous_directory);
                }
                else if (num_args > 0 && strcmp(args[0], "proclore") == 0) {
                    proclore(args + 1, num_args - 1 , root );
                }
                else{
                    syst_call(args, num_args,command , head , time  , background);
                }

            }
        }
    }
    else{
        printf("Invalid command\n");
    }
}
