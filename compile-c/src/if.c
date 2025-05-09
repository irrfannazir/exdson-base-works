#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void if_execution(){
    char temp[4*MAX];
    char condition[MAX];
    strcpy(condition, serialize(parametre_list[parametre_index][0], parametre_list[parametre_index][1]));
    sprintf(temp, "if(%s){}", condition);
    pgm = append_at_index(pgm, temp, pgm_cursor);
    pgm_cursor += strlen(temp);
    // printf("Find the pgm_cursor at %d\n", pgm_cursor);
    // block_cursor[block_cursor_size] = 0;
    // block_cursor_size++;
    pgm_cursor -= 1;
}

void else_execution(){
    char temp[MAX];
    sprintf(temp, "else{}");
    pgm = append_at_index(pgm, temp, pgm_cursor);
    pgm_cursor += strlen(temp) - 1;
}
