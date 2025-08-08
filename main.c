#include <stdio.h>
#include "lex/lex.h"
#include "alt-parse/parse.h"
#include "alt-compile/compile.h"
#include "constants.h"




int main(int argc, char *argv[]){
    const int8_t isinput = argc == 1;
    lexf(isinput, argv[1]);
    parsef();
    compilef();
    flushf();
    return 0;
}