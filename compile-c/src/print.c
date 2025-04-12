#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include <stdio.h>
#include <string.h>

void print_execution_with_array(int *include_cursor){
    int j = 0;
    char format[MAX] = "";
    char parametre_value[MAX] = "";
    char temp[4*MAX];
    while(parametre_list[i][j] != -1){
        if(type[parametre_list[i][j]] == t_string){
            strcat(format, token[parametre_list[i][j]]);
        }else if(type[parametre_list[i][j]] == t_integer){
            strcat(format, token[parametre_list[i][j]]);
        }else if(type[parametre_list[i][j]] == t_identifier){
            strcat(format, "%d");
            strcat(parametre_value, token[parametre_list[i][j]]);
        }
        j++;
    }
    if(strcmp(parametre_value, "") == 0){
        sprintf(temp, "printf(\"%s\");", format);
    }else{
        sprintf(temp, "printf(\"%s\", %s);", format, parametre_value);
    }
    pgm = append_at_index(pgm, temp, pgm_cursor);
    pgm = append_library(pgm, "<stdio.h>", 0);
    *include_cursor += 18;
    pgm_cursor += 18;
}