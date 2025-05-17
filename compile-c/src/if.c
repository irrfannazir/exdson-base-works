#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include "../fileh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void if_execution(){
    char temp[PROGRAM_TEMP_MAX];
    char condition[PARAMETRE_PROGRAM_TEMP_MAX];
    strcpy(condition, serialize(parametre_list[parametre_index][0], parametre_list[parametre_index][1]));
    sprintf(temp, "if(%s){}", condition);
    write_file(PGM_EXATED_FILE_NAME, temp, pgm_cursor);
    pgm_cursor += strlen(temp);
    pgm_cursor -= 1;
}

void else_execution(){
    char temp[PROGRAM_TEMP_MAX];
    sprintf(temp, "else{}");
    write_file(PGM_EXATED_FILE_NAME, temp, pgm_cursor);
    pgm_cursor += strlen(temp) - 1;
}

