#include <string.h>
#include "parse/parseState.h"
#include "data.h"

int compare_the_word(char *word, char *token){
    if(!word || !token) return 0;
    return strcmp(word, token) == 0;
}

int save_type_in_buffer(char *buffer, int index){
    const char *token = get_token(index);
    if(strlen(buffer) + strlen(token) + 2 >= BUFFER_MAX) return 1;
    strcat(buffer, token);
    strcat(buffer, "|\0");
    return 0;
}