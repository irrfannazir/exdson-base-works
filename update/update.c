#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

char var[20][MAX];
int var_len = 0;
int var_index[MAX];

int isand = 0;



int main(){
    int function_num = 0;
    int version_num = 0;
    int case_num = 1;
    // saveToFile(version_num, case_num);
    readFromFile(&version_num, &case_num);
    
    // Add the body of function_name in parse.c
    add_body_in_parse(function_num, version_num, case_num);
    
    // Add the function_name in declare.h
    add_body_in_declare_header(function_num, version_num);
    
    // Add the body of function in declare.c
    // Add the new_function_name in exec.c
    // Add the function body in exec.c
    add_body_in_declare(function_num, version_num, case_num);
    version_num++;
    case_num++;
    saveToFile(version_num, case_num);
    return 0;
}

