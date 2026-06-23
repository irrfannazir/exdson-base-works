#include <stdio.h>
#include "lex.h"
#include "parse.h"
#include "compile.h"
#include "common/constants.h"
#include "lex/lfn.h"
#include "data.h"

#define C_PGM_FILENAME "pgm.c"



int main(int argc, char *argv[]){
    const int8_t isinput = argc == 1;
    lexf(isinput, argv[1], LEX_HANDLING_FILE_NAME);
    parsef(PARSING_HANDLING_FILE_NAME);
    compilef(PARSING_HANDLING_FILE_NAME, C_PGM_FILENAME);
    flushf();
    return 0;
}
