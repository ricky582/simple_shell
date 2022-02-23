#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "Methods.c"
#include "stdlib.h"



int main(int argc, char *argv[]){

//printf ("\nProgram Start.....\n\n");

char *userInput;
userInput = malloc(sizeof(char) * 512);
    char cwd[256];
    char *original =getenv("PATH");
    char *home = getenv("HOME");
    setenv("PATH", home, 1);
    chdir(home);
    //setenv("PATH", "GIBBEr", 1);
    //printf("PATH : %s\n", getenv("PATH"));
    printf("SSH>");
    while(fgets(userInput, 512, stdin)){
        //printf("userInput:%s",userInput);

        if(strncmp(userInput, "exit", 4) ==0) {
            setenv("PATH", original,1);
    //printf("PATH : %s\n", getenv("PATH"));
            //printf("\n");
            return 0;
        }
        parse(userInput);
        printf("The current working directory: %s \n", getcwd(cwd, sizeof(cwd)));
        printf("SSH>");
        
        
    }

    return 0;


}






