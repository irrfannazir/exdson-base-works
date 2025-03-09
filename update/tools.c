#include <stdio.h>
#include <string.h>
#include "file.h"


int check_var(char *str) {
    int i = 0;
    
    // Check if str matches any element in var
    while (i < var_len) {
        if (strcmp(str, var[i]) == 0) {
            return i;  // Return the index if found
        }
        i++;
    }
    
    return -1;  // Return -1 if not found
}


char *datatype(char token){
    switch(token){
        case 'd':
        return "t_datatype";
        case 'i':
            return "t_identifier";
    }
    return "";
}