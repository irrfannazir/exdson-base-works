#include "../data.h"
#include "lexh.h"
#include "append_fh.h"
#include <stdio.h>
#include <string.h>

int appended_indent = 0;


void newline(){
    appended_indent = 0;
}

void check_indent(int *space_count){
    (*space_count)++;
    appended_indent = 0;
}

void append_indent(int *space_count){
    if((*space_count) % 2 != 0){
        perror("Indentation error.");
    }else if(appended_indent == 0){
        append_indent_to_file(LEX_HANDLING_FILE_NAME, (*space_count) / 2);
        appended_indent = 1;
    }
    *space_count = 0;
}



