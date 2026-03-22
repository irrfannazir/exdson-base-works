#include <stdio.h>
#include "lex/lex.h"
#include "alt-parse/parse.h"
#include "alt-compile/compile.h"
#include "include/constants.h"

#define LEX_HANDLING_FILENAME "lex.txt"



int main(int argc, char *argv[]){
    const int8_t isinput = argc == 1;
    lexf(isinput, argv[1], LEX_HANDLING_FILENAME);
    parsef();
    compilef();
    flushf();
    return 0;
}
