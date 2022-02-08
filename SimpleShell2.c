#include <stdio.h>
#include <string.h>
#include <signal.h>
int status = 0; 
int flag =1;
int main(void){
do {
printf("SSH>");
status = read();
}
while (status == 0);
return 0;
}
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

int parse(char input [512]){
    char * token = strtok(input, " \\n \\t \| \< \> \& \;");
     while(token != NULL ) {
      printf( " %s\n", token ); //printing each token
      token = strtok(NULL, "  \\n \\t \| \< \> \& \;");}
      return 0;
}
