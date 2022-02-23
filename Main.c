#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "Methods.c"


int main(int argc, char *argv[]){

    char *userInput;
    userInput = malloc(sizeof(char) * 512);
    //prompt for input
    printf("SSH>");
    while(fgets(userInput, 512, stdin)){
            
        //dumps input buffer if input is larger than character limit
        if (*(userInput + strlen(userInput)-1) != '\n'){
            for (int c; (c = getchar()) != EOF && c != '\n';);
        }

        if(strncmp(userInput, "exit", 4) ==0) { //exit command
            return 0;
        }

        //input is parsed
        parse(userInput); 

        //next prompt for input
        printf("SSH>");
    }
    return 0;
}