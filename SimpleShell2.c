#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "reader.c"

int status =0;
int main(void){
do {
printf("SSH>");
status = reader();
}
while (status == 0);{

return 0;}
}



