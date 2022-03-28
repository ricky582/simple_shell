#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "header.h"
#include "stdlib.h"
char cwd[256];

void setpath(char * tokens[]){ //uses setenv function to change environmnet
    if(tokens[1] == NULL){
        printf("Error: nothing to set path to\n");
    }
    else if (tokens[2] != NULL){
        printf("Error: Too many paremeters\n");} 
    else{
        setenv("PATH", tokens[1] , 1);
    }   
}

void enterIntoArray(char input [512]){ //enters commands into the history array
    char *tempInput = malloc(sizeof(char)*512);
    strcpy(tempInput, input); //we copy input so it can be tokenised without being altered
    char *val = malloc(sizeof(char)*512);
    char *token = strtok(tempInput, " \n\t|<>&;");
    int exit = 0;
    if (token != NULL){ //checks if command is actually an alias which calls history, in which case it is not added
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
        while(token != NULL ) { //builds tokenised input back up - this is to make sure no unwanted characters (e.g. spaces, newlines etc)
            token = strtok(NULL, " \n\t|<>&;");
            if (token != NULL){
                strcat(val, " ");
                strcat(val, token);
            }
        }
        if (count == 20){ // array is shifted if full
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

void cd(char * tokens[]){ //uses chdir function to mimic cd
    char *home = getenv("HOME");
    if (tokens[1] == NULL){
        chdir(home);
    }
    else if(tokens[2] != NULL){
        printf("Error: Too many parameters\n");
    }
    else{
        if (chdir(tokens[1]) != 0){
           char * wrong = tokens[1]; 
            perror(wrong);
        }
    }
}

void getpath(char * tokens[]){ //uses getenv to print path
    if(tokens[1] != NULL){
        printf("Error: Too many paremeters\n");
    }
    else {
        printf("PATH : %s\n", getenv("PATH"));
    }
}

void unalias(char * target){ //removes an alias
    int found = 0;
    if (alSize == 0){
        printf("Error: Alias list is empty!\n");
    }
    else{
        for (int i = 0; i<alSize;i++){
            if (strcmp(aliasList[i].key[0],  target) == 0){ //once target alias is found the list is shifted over it and alSize is reduced
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

void alias(char *key, char *value){ //adds an alias
    char *tempValue = malloc(sizeof(char)*512);
    strcpy(tempValue, value);   //prepares value to be tokenised
    int status = 0;    //indicates when the process should proceed and when it should fail (0 = dont proceed, 1 = proceed, -1 = error)
    int found;
    char *first = strtok(tempValue, " \n\t|<>&;");
    if (strcmp(key, first)==0){     //we dont want our key to match the value as it will create an infinite loop
        status = -1;
    }
    while (status ==0){     //detects and avoids alias loops
        found = 0;
        for (int i = 0; i<alSize;i++){
            if (strcmp(aliasList[i].key[0], first) == 0){ //loop can only continue if it keeps finding more of the chain
                strcpy(tempValue, aliasList[i].value[0]);
                first = strtok(tempValue, " \n\t|<>&;"); //first will keep updating as we go through the alias chain
                if (strcmp(first, key) == 0){ //if the chain forms a loop, alias isnt added
                    status = -1;
                }
                found =1;
            }
        }
        if (found == 0){ //if we reach the end of the chain, alias is OK to add
            status =1;
        }
    }
    if(status == 1){
        for (int i = 0; i<alSize;i++){ //if alias has a key which has already been mapped, we remove the old one with unalias
            if (strcmp(*(aliasList[i].key), key) == 0){
                printf("Alias already exists!\n");
                printf("Overwriting...\n");
                unalias(key);
            }
        }
        if (alSize == 10){
            printf("Error: Maximum aliases reached!\n");
        }
        else{ //adds alias to list
            aliasList[alSize].key[0] = malloc(sizeof(char)*512);
            aliasList[alSize].value[0] = malloc(sizeof(char)*512);
            strcpy(aliasList[alSize].key[0], key);
            strcpy(aliasList[alSize].value[0], value);
            alSize++;
        }
    }
    else printf("Alias would create a loop!\nAborting...\n");
}

int checkHistory(char *key, char *value, int c){ //if an alias holds a history invocation as its value, this function can check for loops
    int isNext = 0;
    char *nextVal = malloc(sizeof(char)*512);
    int pos = 0;
    if (strcmp("!!", value)==0){ //!! is always safe as after a history invocation is aliased, the key wont appear in history
        return 0;
    }
    else{ //takes number from command and transaltes it into the number in history we need to check for an infinite loop
        pos = strtol(value+1, NULL, 10);
        if (pos > 0 && pos <=count){
            pos = pos-1;
        }
        else if ((pos < 0 && pos >=-count)){
            pos = count+pos;
        }
        else return 0; //if the number is out of range its safe
    }
    if (strcmp(commands[pos], key)==0){ //will only abort when it finds the loop
        printf("History invocation aborted to prevent loop!\n");
        return 1;
    }
    for (int i = 0; i<alSize;i++){ //searches for next in history chain
        if(strcmp(commands[pos], *(aliasList[i].key))==0 && isNext == 0){
            if  (strncmp("!", aliasList[i].value[0], 1) == 0){
                isNext = 1;
                strcpy(nextVal, aliasList[i].value[0]);
            }
        }
    }
    if (isNext == 0){ //end of chain reached so its safe
        return 0;
    }
    if (c == 20){ //if we recursivley call 20 times its impossible for this alias to be responsible for the loop, and we let the shell parse the next in the chain
        return 0;
    }
    else{ //recursive call to look for bigger loops
        return checkHistory(key, nextVal, c+1);
    }
}

int parse(char input [512]){
    char *tempInput = malloc(sizeof(char)*512);
    strcpy(tempInput, input); //input is copied so it can be tokenised safely
    char * tokens[512];
    char * token = strtok(tempInput, " \n\t|<>&;");
    tokens[0] = token; 
    int i = 1;
    while(token != NULL ) { //input is converted into an array so it can be easily accessed
        token = strtok(NULL, " \n\t|<>&;");
        tokens[i] = token;
        i++;
    }
    if(tokens[0] == NULL){ //if input is empty after tokenisation we pass it to execute early to avoid errors
        execute(tokens);
        return 0;
    }
    for (int i = 0; i<alSize;i++){
        if (strcmp(*(aliasList[i].key), tokens[0]) == 0){ //checks if input is actually an alias key
            int skip = 0;
            if (strncmp("!", *(aliasList[i].value), 1)==0){ //checks for history loops
                char *value = malloc(sizeof(char)*512);
                char *key = malloc(sizeof(char)*512);
                strcpy(value, aliasList[i].value[0]);
                strcpy(key, aliasList[i].key[0]);
                skip = checkHistory(key,value,0);
            }
            if (skip == 0){ 
                char *val = malloc(sizeof(char)*512);
                int j = 1;
                strcat(val, *(aliasList[i].value));
                while (tokens[j] != NULL){ //adds extra input as parameters
                    strcat(val, " ");
                    strcat(val, tokens[j]);
                    j++;
                }
                parse(val); //alias is parsed like normal
            }
            return 0; //exit early to avoid commands being called twice
        }
    }
    if(strcmp(tokens[0], "!!") ==0 ){ //executes last command from history
        if (tokens[1] == NULL){
        if (count > 0){
            parse(commands[count-1]);
        }
        else{
            printf("Error: No history!\n");
        }
        }else printf("Error: too many parameters!\n");
    }
    else if(strcmp(tokens[0], "history") ==0 ){ //prints history
        if(tokens[1] != NULL){
            printf("Error: Too many parameters\n");
        }
        else {
            for (int i = 0; i<count; i++){
                printf("%d  %s\n",i+1 ,commands[i]);
            }
        }
    }
    else if(strncmp(tokens[0], "!", 1) ==0 ){  //history invocation by number
        if (tokens[1] == NULL){
        char *ptr;
        int no = strtol((tokens[0]+1), &ptr ,10);
        if(count > 0){
            if (no > 0 && no <= count){
                parse(commands[no-1]);
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
        }else printf("Error: too many parameters!\n");
    }
    else if(strcmp(tokens[0], "unalias") ==0 ){  //calls unalias command
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
    else if(strcmp(tokens[0], "alias") ==0 ){ //calls alias command to list/set aliases
        if (tokens[1] != NULL && tokens[2] == NULL){
            printf("Error: Not enough Parameters\n");
        }
        else if (tokens[1] == NULL){ //no parameters means we simply print the alias list
            if (alSize == 0){
                printf("No aliases set yet\n");
            }
            else {
                for (int i = 0; i<alSize;i++){
                    printf("%d. Key: %s  Value: %s\n", (i+1), *(aliasList[i].key), *(aliasList[i].value));
                }
            }
        }
        else{ //input is concatenated back into a string and aliased
            char *val = malloc(sizeof(char)*512);
            int i = 3;
            strcpy(val, tokens[2]);
            while (tokens[i] != NULL){ 
                strcat(val, " ");
                strcat(val, tokens[i]);
                i++;
            }
            alias(tokens[1], val);
        }
    }
    else if(strcmp(tokens[0], "setpath") ==0 ){ //calls setpath function
        setpath(tokens);
    }
    else if(strcmp(tokens[0], "getpath") ==0 ){ //calls getpath function
        getpath(tokens);
    }
    else if (strcmp(tokens[0], "cd") ==0 ){ //calls cd function
        cd(tokens);
    }
    else{ //any other input is handled by execute
        execute(tokens);
    }
    return 0;
}

int execute(char * tokens[]){ //for system and misc commands
    char * token =tokens[0] ;
    pid_t pid = fork(); 
    if (pid < 0) { //failing child
        perror("Error!");
    }
    else if (pid  == 0) { //child uses execvp to try and run command
        if (execvp(tokens[0], tokens) == -1) {
            char * errormsg = tokens[0];
            perror(errormsg);
            exit(0);
        }
    }
    else { //parent
        wait(NULL);
    }
    return 0;
}

void save_file_alias(){ //saves aliases to file
    FILE *file;
    char *home = malloc(sizeof(char)*512);
    strcpy(home, getenv("HOME"));
    home = strcat(home, "/.aliases.txt"); //makes sure our file is always saved in the users home
    file= fopen(home,"w");
    for (int i = 0; i<alSize; i++){ //file is formatted in a very similar way to when 'alias' is called
        fprintf(file,"%d %s %s\n",i+1 , aliasList[i].key[0], aliasList[i].value[0]);
    }
    fclose(file);
}

void save_file_hist(){ //saves history to file
    FILE *file;
    char *home = malloc(sizeof(char)*512);
    strcpy(home, getenv("HOME"));
    home = strcat(home, "/.hist_list.txt"); //makes sure our file is always saved in the users home
    file= fopen(home,"w");
    for (int i = 0; i<count; i++){ //file is formatted in the same way to when 'history' is called
        fprintf(file,"%d %s\n", i+1, commands[i]); 
    }
    fclose(file);
}

void load_file_alias(){ //loads aliases from file
    char *line;
    char *key[511];
    char *value[511];
    int i;
    line = malloc(sizeof(char)*512);
    FILE *file;
    file= fopen(".aliases.txt","r");
    if(file==NULL){ //read mode doesnt create a file when it is used so we must create one manually
        printf("Alias file not detected, creating new...\n");
        file = fopen(".aliases.txt","w");
    }else if(file!=NULL && fgets(line, 512, file) != NULL){
        do {
            i = strtol(line, &line, 10); //must be a number at start of line in the range 1 to 10 to be added, ignored otherwise
            if (i>0 && i<=10){
                key[0] = malloc(sizeof(char)*512);
                value[0] = malloc(sizeof(char)*512);
                key[0] = strtok(line, " "); //first (non-number) token is the key
                if (key != NULL){ //if key is null we ignore the line
                    value[0] = strtok(NULL, "\n"); //instead of splitting by spaces for value we just pull everything up to the end of the line
                    if (value[0] != NULL){ //if value is null we also ignore the line
                        alias(*key, *value);
                    }
                }
            }
        }
        while (fgets(line, 512, file) != NULL);
    }
    fclose(file);
}

void load_file_hist(){ //loads history from file
    FILE *file = NULL;
    file = fopen(".hist_list.txt","r");
    if(file==NULL){ //read mode doesnt create a file when it is used so we must create one manually
        printf("History file not detected, creating new...\n");
        file = fopen(".hist_list.txt","w");
    }else{
        char *historyLine = malloc(512);
        while(fgets(historyLine, 512, file) != NULL) {
            int i = strtol(historyLine, &historyLine, 10); //must be a number at start of line in the range 1 to 20 to be added, ignored otherwise
            if (i>=1&&i<=20){
                historyLine = strtok(historyLine, "\n"); //everything after number is pulled and added to history
                enterIntoArray(historyLine);
            }
        }
        fclose(file);
    }
}