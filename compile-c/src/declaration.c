#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include "../fileh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void declaration_execution(){
    int datatype = parametre_list[parametre_index][0];
    char temp[PROGRAM_TEMP_MAX];
    if(strcmp(token[datatype], "single") == 0){
        sprintf(temp, "int %s = %s;", token[parametre_list[parametre_index][1]], serialize(parametre_list[parametre_index][2], parametre_list[parametre_index][3]));
        write_file(PGM_EXATED_FILE_NAME, temp, pgm_cursor);
        pgm_cursor += strlen(temp);
    }
}
