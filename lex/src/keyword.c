#include "../data.h"
#include <string.h>
#include <stdio.h>


char datatypes[DATATYPE_NAME_SIZE][DATATYPE_SIZE] = {
    "single",
    "array"
};
char datatype_input[DATATYPE_INPUT_LENGTH][DATATYPE_INPUT_ARRAY_SIZE][DATATYPE_SIZE] = {
    {"%d", "%f", "\'%c\'", "\0"},
    {"${%a}", "$\"%s\"", "\0"}
};
const char *keywords[] = {"if", "else", "elif", "new"};
int num_datatype = 2;


// void display_datatype_list(){
//     printf("Datatype List:\n");
//     for (int i = 0; i < num_datatype; i++) {
//         printf("%s\n", datatypes[i]);
//     }
//     printf("\nDatatype Input List:\n");
//     for (int i = 0; i < num_datatype; i++) {
//         for (int j = 0; j < DATATYPE_INPUT_ARRAY_SIZE && datatype_input[i][j][0] != '\0'; j++) {
//             printf("%s ", datatype_input[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }

void new_input(int i){
    int k = i + 1;
    while(
        type[k] == t_identifier
            &&
        strcmp(token[k + 1], "->") == 0
            &&
        type[k + 2] == t_string
    ){
        int j = 0;
        while(token[k + 2][j] != '\0'){
            datatype_input[num_datatype][(k - (i + 1))/3][j] = token[k + 2][j];
            j++;
        }
        datatype_input[num_datatype][(k - (i + 1))/3][j] = '\0';
        k += 3;
    }
    if(k == i + 2){
        strcpy(datatype_input[num_datatype][0], "%s");
        strcpy(datatype_input[num_datatype][1], "\0");
    }else{
        strcpy(datatype_input[num_datatype][(k - (i + 1))/2], "\0");
    }
    num_datatype++;
}

void filter_keyword(){
    int is_new;
    int j;
    for(int i = 0; i < token_size; i++){
        if(type[i] == t_identifier){
            const int keyword_size = sizeof(keywords)/sizeof(keywords[0]);
            //Check the keyword present in the tokens
            for(j = 0; j < keyword_size; j++){
                if(strcmp(token[i], keywords[j]) == 0){
                    type[i] = t_keyword;
                    break;
                }
                //Flag when new keyword is present
                if(strcmp(token[i], "new") == 0){
                    is_new = 1;
                }
            }
            if(j != keyword_size){
                //This condition is when type[i] is a keyword
                continue;
            }
            int datatype_size = num_datatype;
            if(is_new == 1){
                int j = 0;
                type[i] = t_datatype;
                while(token[i][j] != '\0'){
                    datatypes[num_datatype][j] = token[i][j];
                    j++;
                }
                datatypes[num_datatype][j] = '\0';
                new_input(i);
                is_new = 0;
                continue;
            }
            for(j = 0;j < datatype_size; j++){
                if(strcmp(token[i], datatypes[j]) == 0){
                    type[i] = t_datatype;
                    break;
                }
            }
        }
    } 
}