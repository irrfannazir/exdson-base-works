#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *tokenize_white_space(const char *input, int n) {
    if (!input || n < 0) return NULL;

    // Make a copy of input to tokenize
    char *copy = strdup(input);
    if (!copy) return NULL;

    char *token = strtok(copy, " \t\n");
    int index = 0;

    while (token != NULL) {
        if (index == n) {
            // Allocate result before freeing copy
            char *result = malloc(strlen(token) + 1);
            if (result) {
                strcpy(result, token);
                free(copy); // free temporary copy
                return result;
            } else {
                free(copy);
                return NULL; // malloc failed
            }
        }
        token = strtok(NULL, " \t\n");
        index++;
    }

    free(copy);
    return NULL; // Word not found
}
