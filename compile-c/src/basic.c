#include "../include/basic.h"
#include "../include/str.h"
#include "../data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define LIBRARY_NAME_MAX 50

char *serialize(int start, int end){
    char *res = (char *)malloc(PROGRAM_TEMP_MAX * sizeof(char));
    strcpy(res, "");
    for(int i = start; i < end; i++){
        strcat(res, token[i]);
    }
    return res;
}

char *append_library(char *pgm, const char *library, int end){
    int islib = 0;
    char lib[LIBRARY_NAME_MAX];
    int len = 0;
    for(int i = 0; i < end; i++){
        if(pgm[i] == '<' || pgm[i] == '\"'){
            islib = 1;
            lib[len] = pgm[i];
            len++;
        }else if(pgm[i] == '>' || (islib && pgm[i] == '\"')){
            lib[len] = pgm[i];
            len++;
            if(strcmp(lib, library) == 0){
                return pgm;
            }
            islib = 0;
            len = 0;
        }else if(pgm[i] == '\n'){
            islib = 0;
            len = 0;
        }else if(islib){
            lib[len] = pgm[i];
            len++;
        }
    }
    char temp[PROGRAM_TEMP_MAX];
    sprintf(temp, "#include %s\n", library);
    pgm = append_at_index(pgm, temp, 0);
}

