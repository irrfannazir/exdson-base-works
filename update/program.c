#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "update.h"

int find_index(char *str){
    for (int i = 0; i < identifier_num; i++){
        if(strcmp(identifier_arr[i], str) == 0){
            return i;
        }
    }
    return -1;
}

char *special_cases(char *str){
    int case_num;
    sscanf(str, "%d", &case_num);
    switch(case_num){
        case 0:
            return NULL; // No special case
        case 1:
            return "serialize"; // Example special case
    }
}

int special_found_in_program(int index){
    char temp[MAX_TOKEN_LEN];
    char *case_type = special_cases(identifier_arr[index + 1]);
    strcat(prompt, " %s");
    sprintf(temp, ",\n\t%s(parametre_list[parametre_index][%d], parametre_list[parametre_index][%d])", case_type, index, index + 1);
    strcat(parametre, temp);
    return 0;
}

void token_found_in_program(int index){
    char temp[MAX_TOKEN_LEN];
    sprintf(temp, ",\n\ttoken[parametre_list[parametre_index][%d]]", index);
    strcat(parametre, temp);
    return;
}

void assign(char *str){
    if(strcmp(prompt, "") == 0){
        strcat(prompt, str);
    }else{
        char temp[MAX_TOKEN_LEN];
        sprintf(temp, " %s", str);
        strcat(prompt, temp);
    }
}

void program_command_check(char *str, int i){
    if(str[0] == '$' && str[1] == '$'){
        char temp[MAX_TOKEN_LEN];
        strcpy(temp, str);
        slice(str, 2);
        if(find_index(str) == -1){
            assign(temp);
            return;
        }
        special_found_in_program(find_index(str));
    }
    else if(str[0] == '$'){
        slice(str, 1);
        strcat(prompt, " %s");
        token_found_in_program(find_index(str));
    }else{
        assign(str);
    }
}