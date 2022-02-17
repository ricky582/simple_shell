#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "header.h"







void reader(String input){
   if(fgets(input, 512, stdin) == NULL) {
       
        free(input);
        exit(0);
    }
  

}

void parse(String input, String tokens[]){
    String copy = malloc(sizeof(char)*strlen(input));
    String token = strtok(input, " \n\t|<>&;");
    strcpy(copy,input);
    
  
    int i = 0; //Something is wrong to do with this future Ewan
     while(token != NULL ) {
      //printf( "%s\n", token ); //printing each token
      tokens[i]=malloc(sizeof(char)*strlen(token));
      strcpy(tokens[i],token);
      token = strtok(NULL, " \n\t|<>&;");
      i++;
      
      }
 
    free(copy);
    free(token);
      
}



int execute(String tokens[]){
char * token =tokens[0] ;
 if(strcmp(tokens[0], "exit") == 0) {
            return 1;
}


pid_t pid = fork(); 
pid_t child;
if (pid < 0){
    perror("Error!");
   
}
else if (pid  == 0){

execvp(tokens[0], tokens);
    
    exit(0);
}
else{
child = wait(NULL);
//printf("the child has completed\n");

}

return 0;

}
