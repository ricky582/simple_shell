/* header.h */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

typedef char* String;

void parse(String input, String tokens[]);
void reader();
int execute(String tokens[]);
