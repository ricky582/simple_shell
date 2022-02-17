#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "header.h"
#define max 512


int parse(char input [512]){
    char * tokens[512];
    char * token = strtok(input, " \n\t|<>&;");
    tokens[0] = token; 
    int i = 1;
     while(token != NULL ) {
      //printf( "%s\n", token ); //printing each token
      token = strtok(NULL, " \n\t|<>&;");
      tokens[i] = token;
      
      i++;
      
      }
      execute(tokens);
      return 0;
}


int flag =1;
int reader(){
    FILE *fp;
    char input[512];
    //input = malloc(512 * sizeof(char));
    int status = 0;
    flag = fgets(input,512, stdin);//Change to fgets and check if null then exit if true
    if (flag != NULL){
     parse(input);  
    }else {
      signal(SIGINT, flag);  

    }
                    //allocate memory for tokenised array
                        //parse after if not null
if (strcmp(input, "exit") == 0){
     signal(SIGINT, flag);
    status = 1; 
}
//free(input);
//free memory
return status;}




int execute(char * tokens[]){
char * token =tokens[0] ;
char *argv[511];


int j = 1;
argv[0] = token;
while (tokens[j] != NULL){
argv[j] = tokens[j];
j++;
}
pid_t pid = fork(); 
if (pid < 0){
    perror("Error!");

}
else if (pid  == 0){

execvp(token, argv);
memset(argv, NULL, sizeof(argv));
}
else{
wait(NULL);
//printf("the child has completed\n");

}

return 0;

}