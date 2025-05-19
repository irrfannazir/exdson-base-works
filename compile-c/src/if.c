#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include "../fileh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int findChar(const char *str, char target) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == target) {
            return i;  // Return the index where the character is found
        }
        i++;
    }
    return -1;  // Character not found
}

void if_execution(){
    char temp[PROGRAM_TEMP_MAX];
    char condition[PARAMETRE_PROGRAM_TEMP_MAX];
    strcpy(condition, serialize(parametre_list[parametre_index][0], parametre_list[parametre_index][1]));
    sprintf(temp, "if(%s){}", condition);
    write_file(PGM_EXATED_FILE_NAME, temp, program_cursor[CURRENT_CURSOR]);
    cursor_is_moved(CURRENT_CURSOR, strlen(temp));
    add_cursor(1);
}

void else_execution(){
    char temp[PROGRAM_TEMP_MAX];
    sprintf(temp, "else{}");
    write_file(PGM_EXATED_FILE_NAME, temp, program_cursor[CURRENT_CURSOR]);
    cursor_is_moved(CURRENT_CURSOR, strlen(temp));
    add_cursor(1);
}

