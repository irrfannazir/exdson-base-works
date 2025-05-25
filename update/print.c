#include <stdio.h>
#include "update.h"

void print_string_array(char token[MAX_TOKENS][MAX_TOKEN_LEN], int size){
    printf("\nIdentifier:\n");
    for (int k = 0; k < size; k++) {
        printf("%s\n", token[k]);
    }
}

void print_identifier(struct parametre *a, int size){
    printf("\nTokens as identifier:\n");
    for(int i = 0; i < size; i++){
        printf("Type: %d, Name: %s, Index: %d\n", a[i].type, a[i].name, a[i].index);
    }
}
