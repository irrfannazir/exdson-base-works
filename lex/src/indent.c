#include "../data.h"
#include <stdio.h>
#define MAX 500


void add_indent(int *space_count){
    (*space_count)++;
    if(*space_count%2 == 0){
        indent_token[num_lines(-1)]++;
    }
}

void clear_indent(int *iscolonfound){
    if(*iscolonfound > indent_token[num_lines(-1)]){
        *iscolonfound = indent_token[num_lines(-1)];
    }
}



