#include <stdio.h>
#include <string.h>


int execute(char * token){
pid_t pid = fork(); 
if (pid < 0){
    printf("pid = -1\n");

}
else if (pid == 0){
printf("pid = 0\n");
}
else{
wait(NULL);
printf("Else Triggered\n");
}

return 0;
}