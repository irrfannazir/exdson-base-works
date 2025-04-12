#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void declaration_execution(){
    int datatype = parametre_list[i][0];
    char temp[4*MAX];
    if(strcmp(token[datatype], "single") == 0){
        sprintf(temp, "int %s = %s;", token[parametre_list[i][1]], serialize(parametre_list[i][2], parametre_list[i][3]));
        pgm = append_at_index(
            pgm,
            temp,
            pgm_cursor
        );
        // pgm_cursor += strlen(temp);
    }
}