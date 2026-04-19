#include "headers.h"

int main(){
    char previous_directory[5000];
    char root_dir[5000];
    char* root_dir_buffer = getcwd(root_dir, sizeof(root_dir));
    char file_name[4097];
    snprintf(file_name, sizeof(file_name), "%s/%s", root_dir_buffer, "log.txt");
    char command[5000]; 
    Node* head = LinkedList();
    int time = 0 ;
    while (1) {
        Queue* Q = createQueue(15);
        FILE* file = fopen(file_name , "r");
        char line[4097];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = '\0';
            Q = enqueue(Q , line);
        }
        fclose(file);
        int include = 1 ;
        display(root_dir_buffer, strlen(root_dir_buffer) , &time , command);
        time=0;
        command[0]='\0';
        char input[5000];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        char*rem_semi = strdup(input);
        int background = 0;
        head = _delete(head);
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
                char *token = strtok(remaining_token, " \n\t");
                while (token != NULL) {
                    if(strcmp(token," ")!=0 && strcmp(token,"\t")!=0){
                        args[num_args++] = token;
                    }
                    token = strtok(NULL, " \n");
                }

                if (num_args > 0 && strcmp(args[0], "hop") == 0) {
                    execute_hop(args + 1, num_args - 1 , root_dir_buffer , previous_directory);
                }
                else if (num_args > 0 && strcmp(args[0], "reveal") == 0) {
                    reveal(args + 1, num_args - 1 , root_dir_buffer , previous_directory);
                }
                else if (num_args > 0 && strcmp(args[0], "seek") == 0) {
                    seek(args + 1, num_args - 1 , root_dir_buffer , previous_directory);
                }
                else if (num_args > 0 && strcmp(args[0], "proclore") == 0) {
                    proclore(args + 1, num_args - 1 , root_dir_buffer );
                }
                else if (num_args > 0 && strcmp(args[0], "iman") == 0) {
                    iman(args + 1, num_args - 1 );
                }
                else if (num_args > 0 && strcmp(args[0], "log") == 0) {
                    log_f( args+1 ,num_args-1 , Q , root_dir_buffer , previous_directory ,head, &time ,command);
                    include =0;
                }
                else{
                    syst_call(args, num_args,command , head , &time  , background);
                }

            }
        }
        if(include && strcmp(peek_rear(Q) , input)!=0)
        {
            if(Q->count<15)
            {
                Q = enqueue(Q , strdup(input));
            }
            else{
                Q = enqueue(Q , strdup(input));
                Q = dequeue(Q );
            }
        }
        FILE* file2 = fopen(file_name , "w");
        while(!isEmpty(Q))
        {
            fprintf(file2, "%s\n", peek_front(Q));
            Q = dequeue(Q);
        }
        freeQueue(Q);
        fclose(file2);
        
    }

    return 0;
}