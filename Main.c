#include <stdio.h>
#include <string.h>
#include <signal.h>
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
    load_file_alias();
    load_file_hist();
    printf("SSH>");
    while(fgets(userInput, 512, stdin)){  
        //printf("userInput:%s",userInput);
        if(*(userInput+strlen(userInput)-1) != '\n'){
            for (int c; (c = getchar()) != EOF && c != '\n';);
        } 
        if(strncmp(userInput, "exit", 4) ==0) {
             setenv("PATH", original,1);
            printf("%s\n", getenv("PATH"));
            save_file_hist();
            save_file_alias();
            return 0;
        }
        char *save = malloc(512);
        if (userInput[0] != '!'){
            strcpy(save, userInput);
            enterIntoArray(userInput);
            strcpy(userInput, save);
        }
        char commands2[19][511];
        for (int i = 0; i<count;i++){
            strcpy(commands2[i], commands[i]);
        }
        parse(userInput);
        printf("SSH>");   
        for (int i = 0; i<count;i++){
            strcpy(commands[i], commands2[i]);
        }
    }
    setenv("PATH", original,1);
    printf("%s\n", getenv("PATH"));
    save_file_alias();
    save_file_hist();
    return 0;
}