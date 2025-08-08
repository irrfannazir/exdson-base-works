#include <string.h>
#include <stdio.h>
#include "../../utils/p_error.h"

int compare_the_word(char *word, char *token){
    return strcmp(word, token) == 0;
}
