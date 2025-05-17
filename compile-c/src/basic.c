#include "../include/basic.h"
#include "../include/str.h"
#include "../fileh.h"
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

char *append_library(char *filename, const char *library, int end){
    int islib = 0;
    char lib[LIBRARY_NAME_MAX];
    int len = 0;
    char *pgm = read_file(PGM_EXATED_FILE_NAME);
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
    write_file(PGM_EXATED_FILE_NAME, temp, 0);
}

