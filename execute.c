#include <stdio.h>
#include <string.h>
#include <unistd.h>

int execute(char * tokens[]){
char * token =tokens[0] ;
char *argv[511];


int j = 1;
argv[0] = token;
while (tokens[j] != NULL){
argv[j] = tokens[j];
j++;
}
pid_t pid = fork(); 
if (pid < 0){
    perror("Error!");

}
else if (pid  == 0){

execvp(token, argv);
memset(argv, NULL, sizeof(argv));
}
else{
wait(NULL);
//printf("the child has completed\n");

}

return 0;

}