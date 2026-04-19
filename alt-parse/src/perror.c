#include <stdio.h>
#include "../data.h"

int append_error_message(const char *msg){
    //Stack the error messages to be shown.
}

//To count number of lines
int num_lines(int size){
    if(size == -1){
        size = token_size;
    }
    int res = 0;
    for(int i = 0;i < size; i++){
        if(get_type(i) == TOKEN_EOF){
            res++;
        }
    }
    return res;
}