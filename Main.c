#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "Methods.c"

int status =0;
int main(int argc, char *argv[]){
do {
printf("SSH>");
status = reader();
}
while (status == 0);{

return 0;}
}



