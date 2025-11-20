#include <stdio.h>
#include "compileh.h"
#include "../include/fileh.h"
#include "../data.h"

void add_the_header(const char *filename, const char *headername){
    static char temp[C_PROGRAM_MAX] = "";
    int i = 1;
    int flag = 0;
    sprintf(temp, "#include <%s>\n", headername);
    while(get_nth_line(PGM_EXATED_FILE_NAME, i, NULL, 0)){
        if(strcmp(get_nth_line(PGM_EXATED_FILE_NAME, i, NULL, 0), temp) == 0){
            flag = 1;
            break;
        }
        i++;
    }
    if(!flag){
        insert_before_target(PGM_EXATED_FILE_NAME, temp, INCLUDE_CURSOR);
    }
}