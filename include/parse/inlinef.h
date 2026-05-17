#ifndef INLINEF_H
#define INLINEF_H
#include <string.h>
#include "parseh.h"
#include "strh.h"


static inline int is_variable_redefining(){
    FILE *file = fopen(SYMBOL_TABLE_FILE_NAME, "r");
    char name[NAME_STRLEN];
    while(fgets(name, NAME_STRLEN, file)){
        trim_newline(name);
        if(strcmp(name, working_identifier) == 0){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

static inline int handling_declaration(int mln){
    if(
        working_identifier[0] != '\0' &&
        strstr(get_meaning_from_method(mln), "declare") != NULL
    ){
        if(is_variable_redefining()){
            char temp[1024 + NAME_STRLEN];
            sprintf(temp, "Redefinition of %s", working_identifier);
            push_error(temp);
            return 1;
        }
        fputs_with_newl(SYMBOL_TABLE_FILE_NAME, working_identifier);
    }
    return 0;
}

int method_inline_handling(int mln);

#endif