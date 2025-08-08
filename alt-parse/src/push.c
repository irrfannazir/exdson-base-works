#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parseh.h"
#include "../data.h"

char parsed_token[PARSE_DETAILS_MAX];

int append_token_details(int mln){
    if(strcmp(parsed_token, "") == 0){
        return 0;
    }
    FILE *file = fopen(PARSING_HANDLING_FILE_NAME, "a");
    if(file == NULL){
        __pc_error__("Error while appending the parsed data to file named %s", PARSING_HANDLING_FILE_NAME);
        printf("Error opening file %s\n", PARSING_HANDLING_FILE_NAME);
        return 1;
    }
    fprintf(file, "%d %s\n", mln, parsed_token);
    fclose(file);
    strcpy(parsed_token, "");
    return 0;
}

int create_the_parser_file(){
    FILE *file = fopen(PARSING_HANDLING_FILE_NAME, "w");
    if(file == NULL){
        __pc_error__("Error while creating a file named %s\n", PARSING_HANDLING_FILE_NAME);
        return 1;
    }
    fclose(file);
    return 0;
}

void push_to_parse_string(int index){
    char temp[DIGIT];
    itoa(index, temp, 10);
    strcat(parsed_token, temp);
    strcat(parsed_token, " ");
}
