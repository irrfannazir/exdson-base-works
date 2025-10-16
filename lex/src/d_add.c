#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data.h"

#define TOKEN_BLOCK "TOKEN_DATATYPE:"
#define DEFAULT_TEXT "TOKEN_DATATYPE:\n\tsingle\n\tarray\n"


void init_stat() {
    FILE *fp = fopen(PARSE_DATATYPE_LIST_FILE_NAME, "w");
    if (fp == NULL) {
        __pc_error__("Error while initiating datatype list file named %s", PARSE_DATATYPE_LIST_FILE_NAME);
        return;
    }
    fputs(DEFAULT_TEXT, fp);
    fclose(fp);
}

void append_datatype_in_stat(const char *datatype) {
    FILE *fp = fopen(PARSE_DATATYPE_LIST_FILE_NAME, "a");
    if (fp == NULL) {
        __pc_error__("Error while appending datatype to list file named %s", PARSE_DATATYPE_LIST_FILE_NAME);
        return;
    }
    fprintf(fp, "\t%s\n", datatype);
    fclose(fp);
}

char* get_datatype_from_stat(int n) {
    FILE *fp = fopen(PARSE_DATATYPE_LIST_FILE_NAME, "r");
    if (fp == NULL) {
        __pc_error__("Error while retrieving datatype from list file named %s", PARSE_DATATYPE_LIST_FILE_NAME);
        return NULL;
    }

    static char line[256];
    int count = -1;
    int in_block = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (!in_block) {
            if (strncmp(line, TOKEN_BLOCK, strlen(TOKEN_BLOCK)) == 0) {
                in_block = 1;
            }
        } else {
            // End of block
            if (line[0] != '\t') break;  
            count++;
            if (count == n) {
                // Remove trailing newline
                line[strcspn(line, "\n")] = '\0';
                fclose(fp);
                return line + 1;
            }
        }
    }

    fclose(fp);
    return NULL;
}
