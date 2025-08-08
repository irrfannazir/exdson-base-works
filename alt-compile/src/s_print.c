#include <stdio.h>
#include <string.h>
#include "c_constant.h"
#include "compileh.h"
#include "../data.h"



void print_statement(int *arr, int count){
    static char temp[C_PROGRAM_MAX] = "";
    add_the_header(PGM_EXATED_FILE_NAME, "stdio.h");
    // insert_newline_before_target(PGM_EXATED_FILE_NAME, INCLUDE_CURSOR);
    for(int i = arr[1]; i < arr[2]; i++){
        if(strcmp(get_token(i), ",") == 0){
            continue;
        }else if(get_type(i) == TOKEN_STRING || get_type(i) == TOKEN_INTEGER){
            sprintf(temp, "puts(\"%s\");", get_token(i));
        }else if(get_type(i) == TOKEN_IDENTIFIER){
            sprintf(temp, "printf(\"%%d\", %s);\0", get_token(i));
        }
        insert_before_target(PGM_EXATED_FILE_NAME, temp, PGM_CURSOR);
    }
}