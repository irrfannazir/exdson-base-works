#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include "../fileh.h"
#include <stdio.h>
#include <string.h>

void print_execution_with_array(){
    int j = 0;
    char format[PARAMETRE_PROGRAM_TEMP_MAX] = "";
    char parametre_value[PARAMETRE_PROGRAM_TEMP_MAX] = "";
    char temp[PROGRAM_TEMP_MAX];
    while(parametre_list[parametre_index][j] != -1){
        if(type[parametre_list[parametre_index][j]] == TOKEN_STRING){
            strcat(format, token[parametre_list[parametre_index][j]]);
        }else if(type[parametre_list[parametre_index][j]] == TOKEN_INTEGER){
            strcat(format, token[parametre_list[parametre_index][j]]);
        }else if(type[parametre_list[parametre_index][j]] == TOKEN_IDENTIFIER){
            strcat(format, "%d");
            strcat(parametre_value, token[parametre_list[parametre_index][j]]);
        }
        j++;
    }
    if(strcmp(parametre_value, "") == 0){
        sprintf(temp, "printf(\"%s\");", format);
    }else{
        sprintf(temp, "printf(\"%s\", %s);", format, parametre_value);
    }
    write_file(PGM_EXATED_FILE_NAME, temp, program_cursor[CURRENT_CURSOR]);
    cursor_is_moved(CURRENT_CURSOR, strlen(temp));
    append_library(PGM_EXATED_FILE_NAME, "<stdio.h>", program_cursor[FUNCTION_CURSOR]);
}
