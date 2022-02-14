#include <stdio.h>
#include <string.h>
#include <unistd.h>

int execute(char * tokens[]){
char * token =tokens[0] ;
char *argv[511];
printf("This is tokens[0] %s\n", tokens[0]);

printf("This is the token %s\n", token);
int j = 1;
argv[0] = token;
while (tokens[j] != NULL){
argv[j] = tokens[j];
printf("This is argv[%d]: %s and this is tokens[%d]: %s \n", j, argv[j], j, tokens[j]);
i++;
j++;
}
pid_t pid = fork(); 
if (pid < 0){
    perror("Error!");

}
else if (pid  == 0){
printf("I would now run execvp(%s,%s)\n", token, argv); 
execvp(token, argv);
memset(argv, NULL, sizeof(argv));
}
else{
wait(NULL);
printf("the child has completed");

}

return 0;

}