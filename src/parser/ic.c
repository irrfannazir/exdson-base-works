#include <stdio.h>
#include "parse/inlinef.h"



int method_inline_handling(struct parseState ps){
    char *meaning = get_meaning_from_method(ps.method_line_number);
    char *ic_pgm;

    if(!meaning) return 0;
    if(ps.method_line_number + ps.method_token_number == 0) return 0; 
    if(handling_declaration(ps.method_line_number)) return 1;

    // if(!ps.buffer) printf("msg: %s\n", ps.buffer);

    fputs_with_newl(IC_FILENAME, meaning);
    return 0;
}
