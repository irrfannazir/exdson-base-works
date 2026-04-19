#include "../data.h"
#include <stdio.h>

t_type type[TOKEN_SIZE_MAX];
int indent_token[TOKEN_SIZE_MAX];
int token_size;
int total_error;
int dont_compile = 0;


struct Node *root_array[500];


int line_method[LINE_MAX];
int line_size = 0;
int parametre_list[LINE_MAX][PARAMETRE_MAX];

int ismath = 0;
