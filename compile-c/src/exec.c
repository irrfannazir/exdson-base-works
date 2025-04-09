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

char *append_library(char *pgm, const char *library, int end){
    int islib = 0;
    char lib[MAX];
    int len = 0;
    for(int i = 0; i < end; i++){
        if(pgm[i] == '<' || pgm[i] == '\"'){
            islib = 1;
            lib[len] = pgm[i];
            len++;
        }else if(pgm[i] == '>' || (islib && pgm[i] == '\"')){
            lib[len] = pgm[i];
            len++;
            if(strcmp(lib, library) == 0){
                return pgm;
            }
            islib = 0;
            len = 0;
        }else if(pgm[i] == '\n'){
            islib = 0;
            len = 0;
        }else if(islib){
            lib[len] = pgm[i];
            len++;
        }
    }
    char temp[MAX];
    sprintf(temp, "#include %s\n", library);
    pgm = append_at_index(pgm, temp, 0);
}

void add_the_program(){
    int pgm_cursor = 11;
    int include_cursor = 0;
    int function_cursor = 0;
    int datatype;
    int j;
    strcpy(pgm, "int main(){return 0;}");
    char temp[4*MAX];
    for(int i = 0; i < line_size; i++){
        //Memory allocation for line method 1
        char format[MAX] = "";
        char parametre_value[MAX] = "";
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
                    pgm_cursor += strlen(temp);
                }
                break;
            case 1:
                j = 0;
                while(parametre_list[i][j] != -1){
                    if(type[parametre_list[i][j]] == t_string){
                        strcat(format, token[parametre_list[i][j]]);
                    }else if(type[parametre_list[i][j]] == t_integer){
                        strcat(format, token[parametre_list[i][j]]);
                    }else if(type[parametre_list[i][j]] == t_identifier){
                        strcat(format, "%d");
                        strcat(parametre_value, token[parametre_list[i][j]]);
                    }
                    j++;
                }
                if(strcmp(parametre_value, "") == 0){
                    sprintf(temp, "printf(\"%s\");", format);
                }else{
                    sprintf(temp, "printf(\"%s\", %s);", format, parametre_value);
                }
                pgm = append_at_index(pgm, temp, pgm_cursor);
                pgm = append_library(pgm, "<stdio.h>", include_cursor);
                include_cursor += 18;
                pgm_cursor += 18;
                break;
        }
        // printf("%d\n", line_method[i]);
        // display_postfix(root_array[i]);
    }
    printf("\n");
    return;
}