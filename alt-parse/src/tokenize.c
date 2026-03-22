#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *tokenize_white_space(const char *input, int n) {
    if (!input || n < 0) return NULL;

    char *copy = strdup(input);
    if (!copy) return NULL;

    char *token = strtok(copy, " \t\n");
    int index = 0;

    while (token != NULL) {
        if (index == n) {
            char *result = malloc(strlen(token) + 1);
            if (result) {
                strcpy(result, token);
            }
            free(copy);
            return result;
        }
        token = strtok(NULL, " \t\n");
        index++;
    }

    free(copy);
    return NULL;
}