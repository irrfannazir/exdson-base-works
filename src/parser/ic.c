#include <stdio.h>
#include "parse/inlinef.h"



int method_inline_handling(int mln){
    char *ic_pgm = get_meaning_from_method(mln);
    if(!get_meaning_from_method(mln)) return 0;

    if(handling_declaration(mln)) return 1;


    return 0;
}
