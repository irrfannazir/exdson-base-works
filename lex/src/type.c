#include "../data.h"


void error_found(){
    total_error++;
}

int last_in(){
    return type[token_size - 1];
}

int size(){
    return token_size;
}




int num_lines(int size);
void display_token();