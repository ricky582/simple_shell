#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "Methods.c"


int main(int argc, char *argv[]){

//printf ("\nProgram Start.....\n\n");

char *userInput;
userInput = malloc(sizeof(char) * 512);
int bit = 0;

    printf("SSH>");
    while(fgets(userInput, 512, stdin)){
        //printf("userInput:%s",userInput);

        if(strncmp(userInput, "exit", 4) ==0) {
            //printf("breaking");
            return 0;
        }
        parse(userInput);
        
        printf("SSH>");
        
    }
    
    return 0;


}






