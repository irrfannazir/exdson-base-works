#include <stdio.h>
#include "lex.h"
#include "parse.h"
#include "compile.h"
#include "common/constants.h"
#include "lex/lfn.h"
#include "data.h"

int main(int argc, char *argv[]){
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [source.ex]\n", argv[0]);
        return 1;
    }

    const int8_t isinput = argc == 1;
    int status = lexf(isinput, isinput ? NULL : argv[1], LEX_HANDLING_FILE_NAME);
    if (status) {
        flushf();
        return status;
    }

    status = parsef(PARSING_HANDLING_FILE_NAME);
    if (status) {
        flushf();
        return status;
    }

    status = compilef(PARSING_HANDLING_FILE_NAME, PGM_EXATED_FILE_NAME);
    flushf();
    return status;
}
