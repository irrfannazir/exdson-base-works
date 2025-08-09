#define DECLARATION
#include <stdio.h>
#include <string.h>
#include "c_constant.h"
#include "compileh.h"
#include "../data.h"
#include "../fileh/include/file_utils.h"


void declaration_exec(int *arr, int count){
    const char *datatype = find_datatype(arr[ORDER_DATATYPE]);
    const char *id = get_token(arr[ORDER_ID]);
    static char temp[C_PROGRAM_MAX] = "";
    sprintf(
        temp, 
        "%s %s = %s;",
        datatype,
        id, 
        serialize(arr[ORDER_EXPRESSION_START], arr[ORDER_EXPRESSION_END])
    );
    insert_before_target(PGM_EXATED_FILE_NAME, temp, PGM_CURSOR);
}