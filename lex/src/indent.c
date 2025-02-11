#include "indent.h"
#include "..\data.h"
#include <stdio.h>
#define MAX 500


void add_indent(int *iscolonfound, int *space_count){
    if(*iscolonfound){
        (*space_count)++;
        if(*space_count%2 == 0){
            indent_token[num_lines(-1)]++;
        }
    }
}

void clear_indent(int *iscolonfound){
    if(*iscolonfound > indent_token[num_lines(-1)]){
        *iscolonfound = indent_token[num_lines(-1)];
    }
}



