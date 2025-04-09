#include "../data.h"
#include "../include/debug.h"
#include "../include/print.h"
#include "../include/tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int expression(int index, int size){
    for(int i = index; i < index+size; i++){
        if(
            type[i] != t_identifier
                &&
            type[i] != t_op
                &&
            type[i] != t_integer
                &&
            strcmp(token[i], "(") == 0
                &&
            strcmp(token[i], ")") == 0  
        ){
            return 0;
        }
    }
    // printf("6");
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
        }else if(type[i] == t_identifier || type[i] == t_integer){
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
    debug_the_tokens("array", index, size);
    while(i < index + size){
        if(strcmp(token[i], ",") == 0){
            if(dont_expect_comma){
                // printf("Error: Expected an integer value.\n");
                return 0;
            }
            dont_expect_comma = 1;
        }else if(type[i] == t_integer){
            if(!dont_expect_comma){
                // printf("Error: Expected a comma value.\n");
                return 0;
            }
            dont_expect_comma = 0;
        }else{
            // printf("Error: Unexpected token.\n");
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
                type[j] == t_identifier
                    &&
                i - j == 1
            ){
                return 1;
            }else if(
                type[j] == t_identifier
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

int split_with_delimiter(int index, int size, const char delimiter){
    int i = index;
    int expected_delimiter = 0;
    while(i < index+size){
        if(expected_delimiter){
            if(token[index][0] == delimiter){
                expected_delimiter = 0;
            }
        }else{
            if(token[index][0] != delimiter){
                expected_delimiter = 1;
            }else{
                printf("Error: Not expected delimiter %c", delimiter);
                return 0;
            }
        }
        i++;
    }
    return 1;
}

int buffer(int index, int size){
    int i = index;
    int dont_expect_semicolon = 1;
    int dont_expect_datatype = 0;
    int dont_expect_identifier = 0;
    debug_the_tokens("buffer", index, size);
    while(i < index+size){
        if(type[i] == t_datatype){
            if(dont_expect_datatype){
                return 0;
            }else{
                dont_expect_datatype = 1;
                dont_expect_identifier = 0;
                dont_expect_semicolon = 0;
            }
        }
        else if(type[i] == t_identifier){
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
    for(size_t i = 0; i < num_datatype; i++){
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
    // debug_buffer(index, size);
    for(int i = index+size-1; i >= index; i--){
        if(strcmp(token[i], a) == 0){
            return i;
        }
    }
    return -1;
}