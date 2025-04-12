#include "../data.h"
#include <string.h>
#include <stdio.h>

char datatypes[MAX][MAX] = {"single", "array"};
char datatype_input[MAX][MAX] = {"%d", "%a"};
const char *keywords[] = {"if", "else", "elif", "new"};
int num_datatype = 2;



void filter_keyword(){
    int is_new = 0;
    int j;
    for(int i = 0; i < token_size; i++){
        if(type[i] == t_identifier){
            const int limit1 = sizeof(keywords)/sizeof(keywords[0]);
            for(j = 0; j < limit1; j++){
                if(strcmp(token[i], keywords[j]) == 0){
                    type[i] = t_keyword;
                    break;
                }
                if(strcmp(token[i], "new") == 0){
                    is_new = 1;
                }
            }
            if(j != limit1){
                //This condition is when type[i] is a keyword
                continue;
            }
            int limit2 = num_datatype;
            if(is_new == 1){
                type[i] = t_datatype;
                int j = 0;
                while(token[i][j] != '\0'){
                    datatypes[num_datatype][j] = token[i][j];
                    j++;
                }
                if(
                    strcmp(token[i+1], "->") == 0
                        &&
                    token[i+2][0] == '\"'
                ){
                    int j = 1;
                    while(token[i + 2][j] != '\"'){
                        datatype_input[num_datatype][j - 1] = token[i + 2][j];
                        j++;
                    }
                }else{
                    strcpy(datatype_input[num_datatype], "%d");
                }
                datatypes[num_datatype][j] = '\0';
                num_datatype++;
                is_new = 0;
                continue;
            }
            for(j = 0;j < limit2; j++){
                if(strcmp(token[i], datatypes[j]) == 0){
                    type[i] = t_datatype;
                    break;
                }
            }
        }
    }
    for(int i = 0; i < num_lines(-1); i++){
        printf("%d\n", indent_token[i]);
    }
}