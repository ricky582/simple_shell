#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "parse.c"
int flag =1;

int read(){
    char input[512];
    int status = 0;
    flag = gets(input);
if (strcmp(input, "exit") == 0){
    status = 1; 
}
if (flag == 0){
    printf("\n");
    signal(SIGINT, flag);
    status = 1;
} 
parse(input);
return status;}