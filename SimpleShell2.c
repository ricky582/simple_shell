#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "read.c"
int status = 0; 
int main(void){
do {
printf("SSH>");
status = read();
}
while (status == 0);
return 0;
}

