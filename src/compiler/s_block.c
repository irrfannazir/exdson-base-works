#define BLOCK_PARADIGMA
#include <stdlib.h>
#include "compile/sh.h"


void else_condition(const char *dfn){
    char temp[C_PROGRAM_MAX] = "";
    snprintf(temp, sizeof(temp), "else{%s}", PGM_CURSOR);
    insert_before_target(dfn, temp, PGM_CURSOR);
}

void block_paradigm(const char *dfn, char *keyword, int *arr, int count){
    if (count != 3) return;
    char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
    if (!expression) return;
    char temp[C_PROGRAM_MAX] = "";
    snprintf(temp, sizeof(temp), "%s(%s){%s}", keyword, expression, PGM_CURSOR);
    insert_before_target(dfn, temp, PGM_CURSOR);
    char psuedo[PSUEDO_CODE_MAX];
    snprintf(psuedo, sizeof(psuedo), "Start an %s statement block with condition (%s)\n", keyword, expression);
    fputs_with_newl(PARSED_INFORMATION, psuedo);
    free(expression);
}


