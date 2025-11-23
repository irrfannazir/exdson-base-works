#ifndef SYNTAX_H
#define SYNTAX_H
#include <stdlib.h>
#include <string.h>


#define SYNTAX_DIRECTORY "grammar/syntax.txt"
#define METHOD_DIRECTORY "grammar/method.txt"


char *tokenize_white_space(const char *input, int n);


static inline char *find_command_line(char *word) {
    char *marker = strstr(word, "$$");
    if (marker != NULL) {
        *(marker) = '\0';
        return marker + 2;
    }
    return "";
}



#endif