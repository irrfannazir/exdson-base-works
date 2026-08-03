#define PRINT_STATEMENT
#include <stdlib.h>
#include "compile/sh.h"

typedef enum {
    NO,
    TI,
    TO
}p_prev;

static int append_checked(char *dest, size_t dest_size, const char *src) {
    size_t used = strlen(dest);
    size_t add = strlen(src);
    if (used + add + 1 > dest_size) return 1;
    memcpy(dest + used, src, add + 1);
    return 0;
}

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
    if (count != 3) return;
    char format[C_PROGRAM_MAX] = "";
    char para[C_PROGRAM_MAX] = "";
    char temp[C_PROGRAM_MAX*100] = "";
    p_prev flag = NO;
    add_the_header(dfn, "stdio.h");
    // insert_newline_before_target(dfn, INCLUDE_CURSOR);
    for(int i = arr[ORDER_PRINT_START]; i < arr[ORDER_PRINT_END]; i++){
        char *token = get_token(i);
        if (!token) return;
        if(strcmp(token, ",") == 0){
            flag = NO;
        }else if(get_type(i) == TOKEN_STRING){
            if (append_checked(format, sizeof(format), trim_the_string_qoutes(token))) {
                free(token);
                return;
            }
        }else if(get_type(i) == TOKEN_IDENTIFIER || get_type(i) == TOKEN_INTEGER){
            if( strcmp(para, "") == 0 && append_checked(para, sizeof(para), ",")) {
                free(token);
                return;
            }
            switch(flag){
                case NO:
                    if (append_checked(format, sizeof(format), "%d") ||
                        (strcmp(para, ",") != 0 && append_checked(para, sizeof(para), ", ")) ||
                        append_checked(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
                case TI:
                    if (append_checked(format, sizeof(format), "%d") ||
                        append_checked(para, sizeof(para), ", ") ||
                        append_checked(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
                case TO:
                    if (append_checked(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
            }
            flag = TI;
        }else if(get_type(i) == TOKEN_OPERATOR){
            switch(flag){
                case TI:
                    if (append_checked(para, sizeof(para), token)) {
                        free(token);
                        return;
                    }
                    break;
                    default:
                    break;
            }
            flag = TO;
        }
        free(token);
    }
    snprintf(temp, sizeof(temp), "printf(\"%s\"%s);", format, para);
    insert_before_target(dfn, temp, PGM_CURSOR);
    fputs_with_newl(PARSED_INFORMATION, "Implement");
}
