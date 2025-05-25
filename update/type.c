#include <string.h>
#define EXPRESSION 1

char *type_check(char literal){
    switch(literal){
        case 'd':
            return "TOKEN_DATATYPE";
        case 'i':
            return "TOKEN_IDENTIFIER";
    }
    return NULL;
}

int special_type_check(char literal){
    switch(literal){
        case 'e':
            return EXPRESSION;
    }
    return 0;
}