#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "header.h"
#include "Methods.c"
#include <stdlib.h>

int status =0;
String input, tokens[512];

int main(void){
do {

printf("SSH>");

input = malloc(512 * sizeof(char));

reader(input);

parse(input,tokens);

status= execute(tokens);

free(input);
}
while (status == 0);{

return 0;}
}


