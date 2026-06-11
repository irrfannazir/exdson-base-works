#include "compile/sh.h"

typedef enum {
    NO,
    TI,
    TO
}p_prev;

static char *trim_the_string_qoutes(char *line) {
    size_t len = strlen(line);
    if (len > 0 && (
        (line[len - 1] == '"' && line[0] == '"' )||
        (line[len - 1] == '\'' && line[0] == '\'' )||
        (line[len - 1] == '`' && line[0] == '`' )
    )) {
        memmove(line, line + 1, len - 2);
        line[len - 2] = '\0';
        len -= 2;
    }
    return line;
}

void print_statement(const char *dfn, int *arr, int count){
    static char format[C_PROGRAM_MAX] = "";
    static char para[C_PROGRAM_MAX] = "";
    static char temp[C_PROGRAM_MAX*100] = "";
    p_prev flag = NO;
    add_the_header(dfn, "stdio.h");
    // insert_newline_before_target(dfn, INCLUDE_CURSOR);
    for(int i = arr[1]; i < arr[2]; i++){
        if(strcmp(get_token(i), ",") == 0){
            flag = NO;
        }else if(get_type(i) == TOKEN_STRING){
            strcat(format, trim_the_string_qoutes(get_token(i)));
        }else if(get_type(i) == TOKEN_IDENTIFIER || get_type(i) == TOKEN_INTEGER){
            if( strcmp(para, "") == 0 ) strcat(para, ",");
            switch(flag){
                case NO:
                    strcat(format, "%d");
                    strcat(para, get_token(i));
                    break;
                case TI:
                    strcat(format, "%d");
                    strcat(para, ", ");
                    strcat(para, get_token(i));
                    break;
                case TO:
                    strcat(para, get_token(i));
                    break;
            }
            flag = TI;
        }else if(get_type(i) == TOKEN_OPERATOR){
            switch(flag){
                case TI:
                    strcat(para, get_token(i));
                    break;
                default:
                    break;
            }
            flag = TO;
        }
    }
    sprintf(temp, "printf(\"%s\"%s);", format, para);
    insert_before_target(dfn, temp, PGM_CURSOR);
}