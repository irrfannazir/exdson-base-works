#include "../data.h"
#include "../parse/include/tree_node.h"
#include "../include/str.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char *serialize(int start, int end){
    char *res = (char *)malloc(MAX * sizeof(char));
    strcpy(res, "");
    for(int i = start; i < end; i++){
        strcat(res, token[i]);
    }
    return res;
}

void add_the_program(){
    int pgm_cursor = 11;
    int include_cursor = 0;
    int function_cursor = 0;
    int datatype;
    strcpy(pgm, "int main(){return 0;}");
    char temp[MAX];
    for(int i = 0; i < line_size; i++){
        switch(line_method[i]){
            case 0:
                datatype = parametre_list[i][0];
                if(strcmp(token[datatype], "single") == 0){
                    // printf("%s.\n", pgm);
                    // char temp[MAX];
                    sprintf(temp, "int %s = %s;", token[parametre_list[i][1]], serialize(parametre_list[i][2], parametre_list[i][3]));
                    pgm = append_at_index(
                        pgm, 
                        // declaration_string(
                        //     parametre_list[i][1],
                        //     parametre_list[i][2],
                        //     parametre_list[i][3]
                        // ),
                        temp,
                        pgm_cursor
                    );
                }
                break;
        }
        // printf("%d\n", line_method[i]);
        // display_postfix(root_array[i]);
    }
    printf("\n");
    return;
}