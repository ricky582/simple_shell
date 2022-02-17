#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "parse.c"
int flag =1;
int reader(){
    char input[512];
    int status = 0;
    flag = fgets(input, 512, fp) ;//Change to fgets and check if null then exit if true
    if (input == NULL){
     signal(SIGINT, flag);   


    }
    malloc(512);                 //allocate memory for tokenised array
    parse(input);                     //parse after if not null
if (strcmp(input, "exit") == 0){
     signal(SIGINT, flag);
    status = 1; 
}
if (flag == 0){
    printf("\n");
    signal(SIGINT, flag);
    status = 1;
} 
free(input);
//free memory
return status;}