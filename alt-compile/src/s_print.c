#include <stdio.h>
#include <string.h>
#include "c_constant.h"
#include "compileh.h"
#include "../data.h"
#include "../fileh/include/file_utils.h"



void print_statement(int *arr, int count){
    static char format[C_PROGRAM_MAX] = "";
    static char para[C_PROGRAM_MAX] = "";
    static char temp[C_PROGRAM_MAX] = "";
    int flag = 0;
    add_the_header(PGM_EXATED_FILE_NAME, "stdio.h");
    // insert_newline_before_target(PGM_EXATED_FILE_NAME, INCLUDE_CURSOR);
    for(int i = arr[1]; i < arr[2]; i++){
        if(strcmp(get_token(i), ",") == 0){
            continue;
        }else if(get_type(i) == TOKEN_STRING || get_type(i) == TOKEN_INTEGER){
            strcat(format, get_token(i));
        }else if(get_type(i) == TOKEN_IDENTIFIER){
            strcat(format, "%d");
            if(flag){
                strcat(para, ", ");
                strcat(para, get_token(i));
            }else{
                strcat(para, get_token(i));
            }
            flag = 1;
        }
    }
    sprintf(temp, "printf(\"%s\", %s);", format, para);
    insert_before_target(PGM_EXATED_FILE_NAME, temp, PGM_CURSOR);
}