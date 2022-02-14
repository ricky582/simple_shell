#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "execute.c"


int parse(char input [512]){
    char * tokens[512];
    char * token = strtok(input, " \n\t|<>&;");
    printf("This is tokens[0]: %s ",token);
    tokens[0] = token; 
    int i = 1;
     while(token != NULL ) {
      //printf( "%s\n", token ); //printing each token
      token = strtok(NULL, " \n\t|<>&;");
      tokens[i] = token;
      printf("This is tokens [%d]: %s ", i, tokens[i]);
      i++;
      
      }
      execute(tokens);
      return 0;
}