#define DECLARATION
#include <stdlib.h>
#include "compile/sh.h"


void declaration_exec(const char *dfn, int *arr, int count){
    char temp[C_PROGRAM_MAX] = "";
    char psuedo[PSUEDO_CODE_MAX] = "";
    switch(count){
        case 3: //Declaration without assigning
        {
            const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
            char *id = get_token(arr[ORDER_ID]);
            if (!datatype || !id) {
                free(id);
                return;
            }
            char descr[PSUEDO_CODE_MAX];
            get_description(datatype, descr);
            snprintf(
                temp, 
                sizeof(temp),
                "%s %s;",
                datatype,
                id
            );
            snprintf(
                psuedo,
                sizeof(psuedo),
                "Declare a variable named \"%s\" with datatype which %s\n",
                id,
                descr
            );
            free(id);
        }
        break;
        case 5: //Declaration with assigning
        {
            const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
            char *id = get_token(arr[ORDER_ID]);
            char *expression = serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END]);
            if (!datatype || !id || !expression) {
                free(id);
                free(expression);
                return;
            }
            char descr[PSUEDO_CODE_MAX];
            get_description(datatype, descr);
            snprintf(
                temp, 
                sizeof(temp),
                "%s %s = %s;",
                datatype,
                id, 
                expression
            );
            snprintf(
                psuedo,
                sizeof(psuedo),
                "Declare a variable named \"%s\" with datatype which %s and assign the value (%s)\n",
                id,
                descr,
                expression
            );
            free(expression);
            free(id);
        }
        break;
        default:
            return;
    }
    insert_before_target(dfn, temp, PGM_CURSOR);
    fputs_with_newl(PARSED_INFORMATION, psuedo);
}
