#include "../data.h"
#include "../dependencies.h"
#include <string.h>
#include <stdio.h>


char datatypes[DATATYPE_SIZE_MAX][DATATYPE_NAME_SIZE_MAX] = {
    "single",
    "array"
};
char datatype_input[DATATYPE_SIZE_MAX][DATATYPE_INPUT_ARRAY_SIZE][DATATYPE_INPUT_LENGTH] = {
    {"%d", "%f", "\'%c\'", "\0"},
    {"${%a}", "$\"%s\"", "\0"}
};
const char *keywords[] = {"if", "else", "elif", "new"};
int datatype_size = 2;


#ifdef DATATYPE_DISPLAY
void display_datatype_list(){
    printf("Datatype List:\n");
    for (int i = 0; i < datatype_size; i++) {
        printf("%s\n", datatypes[i]);
    }
    printf("\nDatatype Input List:\n");
    for (int i = 0; i < datatype_size; i++) {
        for (int j = 0; j < DATATYPE_INPUT_ARRAY_SIZE && datatype_input[i][j][0] != '\0'; j++) {
            printf("%s ", datatype_input[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
#endif


void new_input(int i){
    int k = i + 1;
    while(
        type[k] == TOKEN_IDENTIFIER
            &&
        strcmp(token[k + 1], "->") == 0
            &&
        type[k + 2] == TOKEN_STRING
    ){
        int j = 0;
        while(token[k + 2][j] != '\0'){
            datatype_input[datatype_size][(k - (i + 1))/3][j] = token[k + 2][j];
            j++;
        }
        datatype_input[datatype_size][(k - (i + 1))/3][j] = '\0';
        k += 3;
    }
    if(k == i + 2){
        strcpy(datatype_input[datatype_size][0], "%s");
        strcpy(datatype_input[datatype_size][1], "\0");
    }else{
        strcpy(datatype_input[datatype_size][(k - (i + 1))/2], "\0");
    }
    datatype_size++;
}

void filter_keyword(){
    int is_new;
    int j;
    for(int i = 0; i < token_size; i++){
        if(type[i] == TOKEN_IDENTIFIER){
            const int keyword_size = sizeof(keywords)/sizeof(keywords[0]);
            //Check the keyword present in the tokens
            for(j = 0; j < keyword_size; j++){
                if(strcmp(token[i], keywords[j]) == 0){
                    type[i] = TOKEN_KEYWORD;
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
            int datatype_size = datatype_size;
            if(is_new == 1){
                int j = 0;
                type[i] = TOKEN_DATATYPE;
                while(token[i][j] != '\0'){
                    datatypes[datatype_size][j] = token[i][j];
                    j++;
                }
                datatypes[datatype_size][j] = '\0';
                new_input(i);
                is_new = 0;
                continue;
            }
            for(j = 0;j < datatype_size; j++){
                if(strcmp(token[i], datatypes[j]) == 0){
                    type[i] = TOKEN_DATATYPE;
                    break;
                }
            }
        }
    }

    #ifdef DATATYPE_DISPLAY
        display_datatype_list();
    #undef DATATYPE_DISPLAY
    #endif
}