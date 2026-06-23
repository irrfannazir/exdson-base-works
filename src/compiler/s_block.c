#define BLOCK_PARADIGMA
#include "compile/sh.h"


void else_condition(const char *dfn, int *arr, int count){
    char temp[C_PROGRAM_MAX] = "";
    sprintf(temp, "else{%s}", PGM_CURSOR);
    insert_before_target(dfn, temp, PGM_CURSOR);
}

void block_paradigm(const char *dfn, char *keyword, int *arr, int count){
    const char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
    char temp[C_PROGRAM_MAX] = "";
    sprintf(temp, "%s(%s){%s}", keyword, expression, PGM_CURSOR);
    insert_before_target(dfn, temp, PGM_CURSOR);
}


