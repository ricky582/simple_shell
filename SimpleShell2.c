#include <stdio.h>
#include <string.h>
int status = 0; 
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
    gets(input);
if (strcmp(input, "exit") == 0){
    status = 1; 
}
if (strcmp(input, "d") == 0){
    status = 1; 
}
if (input == EOF){

    status = 1;
}
return status;
}
