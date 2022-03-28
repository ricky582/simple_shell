/* header.h */
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

char commands[19][511]; //array of strings to store input history
int count; //represents size of commands array

typedef struct Map{ //map structure to represent aliases
    char *key[511];
    char *value[511];
} map ;

map aliasList[10]; //array of maps to represent our alias list
int alSize = 0;

int checkHistory(char *key, char *value, int c);
void alias(char *key, char *value);
void unalias(char * target);
void enterIntoArray(char input [512]);
int parse(char input [512]);
int reader();
int execute(char * tokens[]);
void setpath(char * tokens[]);
void currentCWD();
void cd(char * tokens[]);
void getpath(char * tokens[]);
void save_file_alias();
void save_file_hist();
void load_file_alias();
void load_file_hist();