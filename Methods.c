#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "header.h"
#include "stdlib.h"
void setpath(char * tokens[]){
    if(tokens[1] == NULL){
        perror("Error");
        printf("%s\n", tokens[1]);}
        
    else if (tokens[2] == NULL){
        perror("Error");
        printf("%s\n", tokens[2]);}
    else{ 
        setenv("PATH", tokens[2] , 1);
        
        }


    
}

void getpath(){
    

    }
     else{printf("PATH : %s\n", getenv("PATH"));}
     //printf("PATH : %s\n", getenv("PATH"));
}


int parse(char input [512]){
    char * tokens[512];
    char * token = strtok(input, " \n\t|<>&;");
    tokens[0] = token; 
    int i = 1;
     while(token != NULL ) {
      token = strtok(NULL, " \n\t|<>&;");
      tokens[i] = token;
      
      i++;
      
      }
    if(tokens[0] == NULL){
        execute(tokens);
    }
     else if(strcmp(tokens[0], "setpath") ==0 ){
         
        setpath(tokens);
    
        }

    else if(strcmp(tokens[0], "getpath") ==0 ){
    
        getpath(tokens);
   
        }
      else{
          execute(tokens);}
      return 0;
}





int execute(char * tokens[]){
char * token =tokens[0] ;



pid_t pid = fork(); 
if (pid < 0){
    perror("Error!");

}
else if (pid  == 0){

if(execvp(tokens[0], tokens)==-1);{
    char * errormsg = tokens[0];
    perror(errormsg);


    exit(0);
}
}
else{
wait(NULL);

}

return 0;

}



