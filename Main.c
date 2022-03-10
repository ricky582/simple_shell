#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "Methods.c"
#include "stdlib.h"



int main(int argc, char *argv[]){

char *userInput;
userInput = malloc(sizeof(char) * 512);
    count = 0;
    char cwd[256];
    char *original =getenv("PATH");
    char *home = getenv("HOME");
    chdir(home);
    printf("SSH>");
    while(fgets(userInput, 512, stdin)){
        //printf("userInput:%s",userInput);
        if(*(userInput+strlen(userInput)-1) != '\n'){
            for (int c; (c = getchar()) != EOF && c != '\n';);
        } 
        if(strncmp(userInput, "exit", 4) ==0) {
            setenv("PATH", original,1);
            printf("%s\n", getenv("PATH"));
            return 0;
        }
        if (userInput[0] != '!'){
            enterIntoArray(userInput);
        }
        parse(userInput);
        printf("SSH>");
        
        
    }
    setenv("PATH", original,1);
    printf("%s\n", getenv("PATH"));
    return 0;


}

