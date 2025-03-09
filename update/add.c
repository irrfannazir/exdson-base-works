#include <stdio.h>
#include <string.h>
#include "file.h"

void add_body_in_parse(int fno, int vno, int cno){
    char string_to_add[FINAL_RESULT_MAX];
    const int line_cursor = 22;
    const char *filename = "../parse/parse.c";
    sprintf(string_to_add, "            case %d:\n                __function_%d_%d__(index, size);\n                break;\n", cno, vno, fno);
    // printf("%s", string_to_add);
    write_the_file(filename, string_to_add, line_cursor);
    return;
}

void add_body_in_declare_header(int fno, int vno){
    char string_to_add[FINAL_RESULT_MAX];
    const int line_cursor = 4;
    const char *filename = "../parse/include/declare.h";
    sprintf(string_to_add, "void __function_%d_%d__(int index, int size);\n", vno, fno);
    // printf("%s", string_to_add);
    write_the_file(filename, string_to_add, line_cursor);
}

void add_body_in_declare(int fno, int vno, int cno){
    char string_to_add[FINAL_RESULT_MAX];
    const int line_cursor = 12;
    const char *filename = "../parse/src/declare.c";
    //Take the conditions, parametres saved, execution function
    //For type
    char conditions[MAX] = "";
    char parametres[MAX] = "";
    analyse_the_query(conditions, parametres);
    analyse_the_input(cno);
    sprintf(string_to_add, "\nvoid __function_%d_%d__(int index, int size){\n    if(    \n%s    ){\n%s\n        line_method[line_size] = %d;\n        line_size++;\n        found_the_syntax = 1;\n}\n}\n\n",
        vno,
        fno,
        conditions,
        parametres,
        cno
    );
    // printf("%s", string_to_add);
    write_the_file(filename, string_to_add, line_cursor);
}

