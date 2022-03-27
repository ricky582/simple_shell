#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "header.h"
#include "stdlib.h"
char cwd[256];

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
    char *val = malloc(511);
    char * token = strtok(input, " \n\t|<>&;");
    int exit = 0;
    if (token != NULL){
        for (int i = 0; i<alSize; i++){
            if (strcmp(token, aliasList[i].key[0]) == 0){
                if (strncmp("!", aliasList[i].value[0], 1) == 0){
                    exit = 1;
                }
            }
        }
    }
    if (token != NULL && exit == 0){
        strcpy(val, token);
        while(token != NULL ) {
            token = strtok(NULL, " \n\t|<>&;");
            if (token != NULL){
                strcat(val, " ");
                strcat(val, token);
            }
        }
        if (count == 20){
            int j;
            for (j = 0; j<19; j++){
                strcpy(commands[j], commands[j+1]);
            }
            strcpy(commands[19], val);
        } else {
            strcpy(commands[count], val);
            count ++;
        }
    }
}

void cd(char * tokens[]){
    char *home = getenv("HOME");
    if (tokens[1] == NULL){
        chdir(home);
        }
    else if(tokens[2] != NULL){
        printf("Error: Too many parameters");
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
    else {
        printf("PATH : %s\n", getenv("PATH"));
    }
}


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
    int status = 0;
    int found;
    char *currValue = malloc(512);
    strcpy(currValue, value);
    char *first = strtok(value, " \n\t|<>&;");
    if (strcmp(key, first)==0){
        status = -1;
    }
    while (status ==0){
        found = 0;
        for (int i = 0; i<alSize;i++){
            if (strcmp(aliasList[i].key[0], currValue) == 0){
                if (strcmp(aliasList[i].value[0], key) == 0){
                    status = -1;
                }
                found =1;
                strcpy(currValue, aliasList[i].value[0]);
            }
        }
        if (found == 0){
            status =1;
        }
    }
    if(status == 1){
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
    else printf("Alias would create a loop!\nAborting...\n");
}

int checkHistory(char *key, char *value, int c){
    int isNext = 0;
    char *nextVal = malloc(512);
    int j = 0;
    int safe = 1;
    if (strcmp("!!", value)==0){
        return 0;
    }
    else{
        j = strtol(value+1, NULL, 10);
        if (j > 0 && j <=count){
            j = j-1;
        }
        else if ((j < 0 && j >=-count)){
            j = count+j;
        }
    }
    if (strcmp(commands[j], key)==0){
        printf("History invocation aborted to prevent loop!\n");
        return 1;
    }
    for (int i = 0; i<alSize;i++){
        if(strcmp(commands[j], *(aliasList[i].key))==0 && isNext == 0){
            if  (strncmp("!", aliasList[i].value[0], 1) == 0){
                isNext = 1;
                strcpy(value, aliasList[i].value[0]);
                strcpy(nextVal, aliasList[i].value[0]);
            }
        }
    }
    if (isNext == 0){
        return 0;
    }
    if (c == 20){
        return 0;
    }
    else{
        return checkHistory(key, nextVal, c+1);
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
                found = 1;
                int skip = 0;
                if (strncmp("!", *(aliasList[i].value), 1)==0){
                char *value = malloc(512);
                char *key = malloc(512);
                strcpy(value, aliasList[i].value[0]);
                strcpy(key, aliasList[i].key[0]);
                skip = checkHistory(key,value,0);
                }
                if (skip == 0){
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
                }
            
            }
        }
    }

    if(tokens[0] == NULL){
        if(found == 0){
            execute(tokens);
        }
    }
    else if(strcmp(tokens[0], "!!") ==0 ){
        if (count > 0){
            parse(commands[count-1]);
        }
        else{
            printf("Error: No history!\n");
        }
    }
    else if(strcmp(tokens[0], "history") ==0 ){
        if(tokens[1] != NULL){
            printf("Error: Too many parameters\n");
        }
        else {
            for (int i = 0; i<count; i++){
                printf("%d  %s\n",i+1 ,commands[i]);
            }
        }
    }
    else if(strncmp(tokens[0], "!", 1) ==0 ){
        char *ptr;
        int no = strtol((tokens[0]+1), &ptr ,10);
        int printed = 0;
        if( count > 0){
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
                printf("No command at this number\n");
                printf("Please use a number in the range -%d to %d that is not 0\n", count, count);
            }
        }
        else{
            printf("Error: No history!\n");
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
    else if(strcmp(tokens[0], "setpath") ==0 ){
        setpath(tokens);
    
    }
    else if(strcmp(tokens[0], "getpath") ==0 ){
        getpath(tokens);
   
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

void save_file_alias(){
    FILE *file =NULL;
    char *home = malloc(512);
    strcpy(home, getenv("HOME"));
    home = strcat(home, "/.aliases.txt");
    file= fopen(home,"w");
    for (int i = 0; i<alSize; i++){
        fprintf(file,"%d%s %s\n",i+1 , aliasList[i].key[0], aliasList[i].value[0]);
    }
    fclose(file);
}

void save_file_hist(){
    FILE *file =NULL;
    char *dir = malloc(512);
    char *home = malloc(512);
    strcpy(home, getenv("HOME"));
    dir = strcat(home, "/.hist_list.txt");
    file= fopen(dir,"w");
    for (int i = 0; i<count; i++){
        fprintf(file,"%d %s\n", i+1, commands[i]);
    }
    fclose(file);
}

void load_file_alias(){
    char *line;
    char *key[511];
    char *value[511];
    int i;
    line = malloc(512);
    FILE *file =NULL;
    file= fopen(".aliases.txt","r");
    if(file==NULL){
        printf("Alias file not detected, creating new...\n");
        file = fopen(".aliases.txt","w");
    }else if(file!=NULL && fgets(line, 512, file) != NULL){
        do {
            i = strtol(line, &line, 10);
            if (i>0 && i<=10){
                key[0] = malloc(512);
                value[0] = malloc(512);
                key[0] = strtok(line, " ");
                if (key != NULL){
                    value[0] = strtok(NULL, "\n");
                    if (value[0] != NULL){
                        alias(*key, *value);
                    }
                }
            }
        }
        while (fgets(line, 512, file) != NULL);
    }
    fclose(file);
}

void load_file_hist(){
    FILE *file = NULL;
    file = fopen(".hist_list.txt","r");
    if(file==NULL){
        printf("History file not detected, creating new...\n");
        file = fopen(".hist_list.txt","w");
    }else{
        char *historyLine = malloc(512);
        while(fgets(historyLine, 512, file) != NULL) {
            int i = strtol(historyLine, &historyLine, 10);
            if (i>=1&&i<=20){
                historyLine = strtok(historyLine, "\n");
                enterIntoArray(historyLine);
            }
        }
        fclose(file);
    }
}

int execute(char * tokens[]){
    char * token =tokens[0] ;
    pid_t pid = fork(); 
    if (pid < 0) {
        perror("Error!");
    }
    else if (pid  == 0) {
        if (execvp(tokens[0], tokens) == -1) {
            char * errormsg = tokens[0];
            perror(errormsg);
            exit(0);
        }
    }
    else {
        wait(NULL);
    }
    return 0;
}