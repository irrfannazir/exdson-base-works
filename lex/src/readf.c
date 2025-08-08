#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data.h"

#define MAX_LINE 256
#define MAX_TOKEN 100

char* read_token(const char *filename, int i) {
    FILE *file = fopen(filename, "r");
    if (!file){
        __pc_error__("Error while opening file named %s", filename);
        return NULL;
    }

    static char token[MAX_TOKEN];  // Return buffer (static so it's not deallocated)
    int type;
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        if (count == i) {
            if (sscanf(line, "%d %s", &type, token) == 2) {
                fclose(file);
                return token;
            } else {
                break;  // Line couldn't be parsed
            }
        }
        count++;
    }

    fclose(file);
    return NULL;  // Token not found
}

t_type read_type(const char *filename, int i) {
    FILE *file = fopen(filename, "r");
    if (!file){
        __pc_error__("Error while opening lex file named %s", filename);
        return -1;
    }
    int type;
    char token[MAX_TOKEN];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        if (count == i) {
            if (sscanf(line, "%d %s", &type, token) == 2) {
                fclose(file);
                return (t_type) type;
            } else {
                break;  // Line couldn't be parsed
            }
        }
        count++;
    }

    fclose(file);
    return TOKEN_NULL;
}

int read_indent(const char *filename, int i){
    FILE *file = fopen(filename, "r");
    if (!file) {
        __pc_error__("Error while opening lex file named %s", filename);
        return -1;
    }
    int type;
    char token[MAX_TOKEN];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        if (count == i) {
            if (sscanf(line, "%d %s", &type, token) == 2) {
                if(type == -1){
                    count++;
                }
                fclose(file);
                return atoi(token);
            } else {
                break;  // Line couldn't be parsed
            }
        }
    }

    fclose(file);
    return -1;
}