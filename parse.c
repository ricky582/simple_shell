#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "execute.c"


int parse(char input [512]){
    char * token = strtok(input, " \n\t|<>&;");
     while(token != NULL ) {
      printf( "%s\n", token ); //printing each token
      token = strtok(NULL, " \n\t|<>&;");}
      execute(token);
      return 0;
}