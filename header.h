/* header.h */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
int parse(char input [512]);
int reader();
int execute(char * tokens[]);