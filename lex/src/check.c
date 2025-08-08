#include "../data.h"
#include "d_fh.h"
#include <string.h>

/* Global variable 'isnew' makes function stateful and non-reentrant
 * - Causes side effects between calls
 * - Better to pass as parameter if state needs to be maintained */
int isnew = 0;

/* Missing NULL terminator in keywords array
 * - sizeof() calculation works but is fragile
 * - Better to either:
 *   a) Add explicit NULL terminator: {"if", "else", "elif", "new", NULL}, or
 *   b) Use macro for array size: #define KEYWORD_COUNT 4 */
const char *keywords[] = {"if", "else", "elif", "new"};

void check_datatype(char *token, t_type *type){
    /* No NULL check for input parameters
     * - Should validate: if (!token || !type) return; */
    
    const int keyword_size = sizeof(keywords)/sizeof(keywords[0]);
    
    /* Inefficient double string comparison
     * - First compares with "new", then again in loop
     * - Could combine into single loop with priority check */
    for(int i = 0; i < keyword_size; i++){
        if(strcmp(token, "new") == 0){  // Duplicate check
            *type = TOKEN_KEYWORD;
            isnew = 1;
            return;
        }else if(strcmp(token, keywords[i]) == 0){
            *type = TOKEN_KEYWORD;
            return;
        }
    }

    /* Race condition potential with global 'isnew'
     * - If called concurrently, may get corrupted state */
    if(isnew == 1){
        append_datatype_in_stat(token);
        *type = TOKEN_DATATYPE;
        isnew = 0;
        return;
    }

    /* Memory leak potential
     * - get_datatype_from_stat() may allocate memory
     * - No cleanup shown for 'datatype' values */
    int i = 0;
    char *datatype = get_datatype_from_stat(i);
    i++;
    while(datatype != NULL){
        if(strcmp(token, datatype) == 0){
            *type = TOKEN_DATATYPE;
            return;
        }
        datatype = get_datatype_from_stat(i);
        i++;
    }
    
    /* No default type assignment
     * - Function may return without setting *type
     * - Should have: *type = TOKEN_UNKNOWN at end */
}