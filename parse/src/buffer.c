#include "../data.h"
#include "../include/tree.h"
#include "../include/debug.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int expression(int index, int size){
    for(int i = index; i < index+size; i++){
        if(
            type[i] != TOKEN_IDENTIFIER
                &&
            type[i] != TOKEN_OPERATOR
                &&
            type[i] != TOKEN_INTEGER
                &&
            strcmp(token[i], "(") == 0
                &&
            strcmp(token[i], ")") == 0  
        ){
            return 0;
        }
    }
    int k = parsing_tree_expression(index, size);
    return k;
}

int array_limit_specifier(int index, int size){
    int isopened = 0;
    int found_a_value = 0;
    int i = index;
    while(i < index + size){
        if(strcmp(token[i], "[") == 0){
            if(isopened){
                return 0;
            }
            isopened = 1;
            found_a_value = 0;
        }else if(strcmp(token[i], "]") == 0){
            if(!isopened){
                return 0;
            }
            isopened = 0;
            found_a_value = 1;
        }else if(type[i] == TOKEN_IDENTIFIER || type[i] == TOKEN_INTEGER){
            if(found_a_value){
                return 0;
            }
            found_a_value = 1;
        }else{
            return 0;
        }
        i++;
    }
    return 1;
}

int array(int index, int size){
    int dont_expect_comma = 1;
    int i = index;
    PRINT_TOKENS_FOR_DEBUG(index, size);
    while(i < index + size){
        if(strcmp(token[i], ",") == 0){
            if(dont_expect_comma){
                #ifdef ARRAY_SYNTAX_CHECK
                  printf("Error: Expected an integer value.\n");
                #endif
                return 0;
            }
            dont_expect_comma = 1;
        }else if(type[i] == TOKEN_INTEGER){
            if(!dont_expect_comma){
                #ifdef ARRAY_SYNTAX_CHECK
                  printf("Error: Expected a comma value.\n");
                #endif
                return 0;
            }
            dont_expect_comma = 0;
        }else{
            #ifdef ARRAY_SYNTAX_CHECK
              printf("Error: Unexpected token.\n");
              #undef ARRAY_SYNTAX_CHECK
            #endif
            return 0;
        }
        i++;
    }
    return 1;
}



int identifier_delimiter(int index, int size){
    int i = index;
    int j = index;
    while(i < index+size){
        if(strcmp(token[i], ",") == 0){
            if(
                type[j] == TOKEN_IDENTIFIER
                    &&
                i - j == 1
            ){
                return 1;
            }else if(
                type[j] == TOKEN_IDENTIFIER
                    &&
                strcmp(token[j + 1], "=") == 0
                    &&
                expression(j + 2, index + size - j - 2)
            ){
                return 1;
            }else{
                return 0;
            }
            j = i;
        }
        i++;
    }
}

int buffer(int index, int size){
    int i = index;
    int dont_expect_semicolon = 1;
    int dont_expect_datatype = 0;
    int dont_expect_identifier = 0;
    PRINT_TOKENS_FOR_DEBUG(index, size);
    while(i < index+size){
        if(type[i] == TOKEN_DATATYPE){
            if(dont_expect_datatype){
                return 0;
            }else{
                dont_expect_datatype = 1;
                dont_expect_identifier = 0;
                dont_expect_semicolon = 0;
            }
        }
        else if(type[i] == TOKEN_IDENTIFIER){
            if(dont_expect_identifier){
                return 0;
            }else{
                dont_expect_datatype = 1;
                dont_expect_identifier = 1;
                dont_expect_semicolon = 0;
            }
        }
        else if(strcmp(token[i], ":") == 0){
            if(dont_expect_semicolon){
                return 0;
            }else{
                dont_expect_datatype = 0;
                dont_expect_identifier = 0;
                dont_expect_semicolon = 1;
            }
        }
        i++;
    }
    return 1;
}


int unknown_datatype(char *datatype, int index, int size){
    int datatype_index = -1;
    for(size_t i = 0; i < datatype_size; i++){
        if(strcmp(datatypes[i], datatype) == 0){
            datatype_index = i;
        }
    }
    if(datatype_index == -1){
        printf("Invalid Datatype.\n");
        return 0;
    }
    return 1;
}

int find(int index, int size, char *a){
    for(int i = index+size-1; i >= index; i--){
        if(strcmp(token[i], a) == 0){
            return i;
        }
    }
    return -1;
}