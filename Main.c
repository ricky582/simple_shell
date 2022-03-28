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
    char *original =getenv("PATH"); //original path that gets printed on exit
    char *home = getenv("HOME");
    chdir(home); //makes sure shell always loads in the home directory
    load_file_alias();
    load_file_hist();
    printf("SSH>"); //prompt
    while(fgets(userInput, 512, stdin)){ //input loop
        if(*(userInput+strlen(userInput)-1) != '\n'){ //dumps any excess input if input is too large
            for (int c; (c = getchar()) != EOF && c != '\n';);
        } 
        if(strncmp(userInput, "exit", 4) ==0) {  //if input is exit we end the program before input can be added to history
            setenv("PATH", original,1);
            printf("%s\n", getenv("PATH"));
            save_file_hist();
            save_file_alias();
            return 0;
        }
        if (userInput[0] != '!'){ //any input that is not a history invocation is added to history
            enterIntoArray(userInput);
        }
        parse(userInput);
        printf("SSH>");   
    }
    setenv("PATH", original,1);
    printf("%s\n", getenv("PATH"));
    save_file_alias();
    save_file_hist();
    return 0;
}