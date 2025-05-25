#include "../data.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../include/str.h"
#include "../fileh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void declaration_execution(){
    int datatype = parametre_list[parametre_index][0];
    char temp[PROGRAM_TEMP_MAX];
    if(strcmp(token[datatype], "single") == 0){
        char prev[PROGRAM_TEMP_MAX];
        int op;
        sprintf(temp, "int %s = %s;", token[parametre_list[parametre_index][1]], serialize(parametre_list[parametre_index][2], parametre_list[parametre_index][3]));
        strcpy(prev, read_file(PGM_EXATED_FILE_NAME));
        write_file(PGM_EXATED_FILE_NAME, temp, program_cursor[CURRENT_CURSOR]);
        // printf("The content shifted from: %s\n", read_file(PGM_EXATED_FILE_NAME));
        // scanf("%d", &op);
        if(op != 0){
            // printf("to : %s\n", prev);
            // printf("at %d\n", program_cursor[CURRENT_CURSOR]);
        }
        cursor_is_moved(CURRENT_CURSOR, strlen(temp));
    }
}
