#include <stdio.h>
#include "compileh.h"
#include "../fileh/include/file_utils.h"
#include "../data.h"

void add_the_header(const char *filename, const char *headername){
    static char temp[C_PROGRAM_MAX] = "";
    int i = 1;
    int flag = 0;
    sprintf(temp, "#include <%s>\n", headername);
    while(get_nth_line(PGM_EXATED_FILE_NAME, i)){
        if(strcmp(get_nth_line(PGM_EXATED_FILE_NAME, i), temp) == 0){
            flag = 1;
            break;
        }
        i++;
    }
    if(!flag){
        insert_before_target(PGM_EXATED_FILE_NAME, temp, INCLUDE_CURSOR);
    }
}