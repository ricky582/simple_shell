#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "header.h"
#include "stdlib.h"
char cwd[256];
//char commands[20][512];
//int count = 0;

void setpath(char * tokens[]){
    if(tokens[1] == NULL){
        printf("Error: nothing to set path to\n");
        //perror("Error: nothing to set path to");
    }
        
    else if (tokens[2] != NULL){
        printf("Error: Too many paremeters\n");}
        //perror("Error:Too many paremeters");}
        
    else{

        setenv("PATH", tokens[1] , 1);
        
        }


    
}
void enterIntoArray(char input [512]){
    if (count == 19){
            int i;
            for (i = 0; i<19; i++){
                strcpy(commands[i], commands[i+1]);
            }
            strcpy(commands[19], input);

        } else {
            strcpy(commands[count], input);
            count ++;
        }

}
void currentCWD(){

    printf("The current working directory: %s \n", getcwd(cwd, sizeof(cwd)));;
}


void cd(char * tokens[]){
    char *home = getenv("HOME");
    if (tokens[1] == NULL){
        chdir(home);
        }
    else if(tokens[2] != NULL){

        perror("Too many parameters");
    }
    else{
        if (chdir(tokens[1]) != 0){
           char * wrong = tokens[1]; 
            perror(wrong);
        };

    }
}

void getpath(char * tokens[]){
    if(tokens[1] != NULL){
        printf("Error: Too many paremeters\n");
        //perror("Error:Too many paremeters");
    }

    
    else {printf("PATH : %s\n", getenv("PATH"));}}
    



char cwd[256];
map aliasList[10];
int size = 0;
int alSize = 0;


void setpath(char * tokens[]){
    if(tokens[1] == NULL){
        printf("Error: nothing to set path to\n");
    }
        
    else if (tokens[2] != NULL){
        printf("Error: Too many paremeters\n");}
        
    else{

        setenv("PATH", tokens[1] , 1);
        
        }


    
}
void enterIntoArray(char input [512]){
    if (count == 19){
            int i;
            for (i = 0; i<19; i++){
                strcpy(commands[i], commands[i+1]);
            }
            strcpy(commands[19], input);

        } else {
            strcpy(commands[count], input);
            count ++;
        }

}
void currentCWD(){

    printf("The current working directory: %s \n", getcwd(cwd, sizeof(cwd)));;
}


void cd(char * tokens[]){
    char *home = getenv("HOME");
    if (tokens[1] == NULL){
        chdir(home);
        }
    else if(tokens[2] != NULL){

        perror("Too many parameters");
    }
    else{
        if (chdir(tokens[1]) != 0){
           char * wrong = tokens[1]; 
            perror(wrong);
        };

    }
}

void getpath(char * tokens[]){
    if(tokens[1] != NULL){
        printf("Error: Too many paremeters\n");
    }

    
    else {printf("PATH : %s\n", getenv("PATH"));}}


void unalias(char * tokens){
    int found = 0;
    if (alSize == 0){
        printf("Error: Alias list is empty!\n");
    }
    else{
        for (int i = 0; i<alSize;i++){
            if (strcmp(aliasList[i].key[0], tokens) == 0){
                while (i+1 != alSize){
                    strcpy(aliasList[i].key[0], aliasList[i+1].key[0]);
                    strcpy(aliasList[i].value[0], aliasList[i+1].value[0]);
                    i++;
                }
                found = 1;
                alSize--;
            }
        }
        if (found == 0){
            printf("Error: No such alias to remove!\n");
        }
    }
}

void alias(char *key, char *value){
    for (int i = 0; i<alSize;i++){
        if (strcmp(*(aliasList[i].key), key) == 0){
            printf("Alias already exists!\n");
            printf("Overwriting...\n");
            unalias(key);
        }
    }
    if (alSize == 10){
        printf("Error: Maximum aliases reached!\n");
    }
    else{
        aliasList[alSize].key[0] = malloc(511);
        aliasList[alSize].value[0] = malloc(511);
        strcpy(aliasList[alSize].key[0], key);
        strcpy(aliasList[alSize].value[0], value);
        alSize++;
    }
}

int parse(char input [512]){
    char * tokens[512];
    char * token = strtok(input, " \n\t|<>&;");
    tokens[0] = token; 
    int i = 1;
    int found = 0;
     while(token != NULL ) {
      token = strtok(NULL, " \n\t|<>&;");
      tokens[i] = token;
      
      i++;
      
      }
    if(tokens[0] != NULL){
        for (int i = 0; i<alSize;i++){
            if (strcmp(*(aliasList[i].key), tokens[0]) == 0){
                char *val = malloc(511);
                int j = 1;
                strcat(val, *(aliasList[i].value));
                while (tokens[j] != NULL){
                    strcat(val, " ");
                    strcat(val, tokens[j]);
                    j++;
                }
                char *saveVal = malloc(511); //command must be saved before it is parsed for parameters to remain
                strcpy(saveVal, aliasList[i].value[0]);
                parse(val);
                strcpy(aliasList[i].value[0], saveVal);
                found = 1;
            }
        }
    }
    

    if(tokens[0] == NULL){
        if(found == 0){
            execute(tokens);
        }
    }
    else if(strcmp(tokens[0], "!!") ==0 ){
        if (count ==19){
            parse(commands[count]);
        }
        else if (count != 0){
            parse(commands[count-1]);
        }
        else{
            perror("Command not Found");
        }
    }
    else if(strcmp(tokens[0], "history") ==0 ){
        if(tokens[1] != NULL){
            printf("Error: Too many parameters\n");
        }
        else if (count == 1){
            printf("Error: No history\n");
        }
        else{
            for (int i = 0; i<count; i++){
                printf("%d : %s\n",i+1 ,commands[i]);
            }
        }
    }
    else if(strncmp(tokens[0], "!", 1) ==0 ){
        char *ptr;
        int no = strtol((tokens[0]+1), &ptr ,10);
        int printed = 0;
        if( count < 19){
            if (no > 0 && no <= count){
                printed =1;
                if (printed ==1){
                    parse(commands[no-1]);
                }
            }
            else if (no < 0 && no >= -count){
                parse(commands[count+no]);
            }
            else{
                perror("Command not Found");
            }
        }
        else if( count == 19){
            if(no > 0 && no <= 20){
                parse(commands[no-1]);
            }
            else if (no < 0 && no >= -20){
                parse(commands[20+no]);
            }
            else{
                perror("Command not Found");
            }
        }
        else{
            perror("Command not Found"); //might not need this else
        }


    }
    else if(strcmp(tokens[0], "unalias") ==0 ){   
        if(tokens[1] == NULL){
            printf("Error: Not enough parameters\n");
        }
        else if(tokens[2] != NULL){
            printf("Error: Too many parameters\n");
        }
        else{
            unalias(tokens[1]);
        }
    }
    else if(strcmp(tokens[0], "alias") ==0 ){
        if (tokens[1] != NULL && tokens[2] == NULL){
            printf("Error: Not enough Parameters\n");
        }
        else if (tokens[1] == NULL){
            if (alSize == 0){
                printf("No aliases set yet\n");
            }
            else {
                for (int i = 0; i<alSize;i++){
                    printf("%d. Key: %s  Value: %s\n", (i+1), *(aliasList[i].key), *(aliasList[i].value));
                }
            }
        }
        else{
            
            if (alSize == 10){
                printf("Error: Maximum aliases reached!\n");
            }
            else{
                char *val = malloc(511);
                int i = 3;
                strcat(val, tokens[2]);
                while (tokens[i] != NULL){
                    strcat(val, " ");
                    strcat(val, tokens[i]);
                    i++;
                }
                alias(tokens[1], val);
            }
        }
    }

    else if(strcmp(tokens[0], "setpath") ==0 ){
         
        setpath(tokens);
    
    }

    else if(strcmp(tokens[0], "getpath") ==0 ){
    
        getpath(tokens);
   
    }
    else if(strcmp(tokens[0], "currentCWD") ==0 ){
        currentCWD();   
    }
    else if (strcmp(tokens[0], "cd") ==0 ){
        cd(tokens);

    }
    else{
        if (found == 0) {
            execute(tokens);
        }
    }
    return 0;
}

void save_file(){
    
    FILE *file =NULL;
    file= fopen(".hist_list.txt","w");
    if(file==NULL){
        printf("This file does not seem to exist");
        exit(1);
    }else{

  
     for (int i = 0; i<count; i++){
         
                fprintf(file,"%d  %s",i+1 ,commands[i]);
    }
    fclose(file);
    }
}


int execute(char * tokens[]){
char * token =tokens[0] ;



pid_t pid = fork(); 
if (pid < 0){
    perror("Error!");

}
else if (pid  == 0){

if(execvp(tokens[0], tokens)==-1);{
    char * errormsg = tokens[0];
    perror(errormsg);


    exit(0);
}
}
else{
wait(NULL);

}

return 0;

}



