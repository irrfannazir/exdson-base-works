#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data.h"

#define MAX_LINE_LENGTH 1024

char* get_nth_line_from_parse(int n) {
    static char line[MAX_LINE_LENGTH]; 
    FILE *file = fopen(PARSING_HANDLING_FILE_NAME, "r");

    if (!file) {
        __pc_error__("Error while retrieving line from the file %s", PARSING_HANDLING_FILE_NAME);
        return NULL;
    }

    int current_line = 1;
    while (fgets(line, sizeof(line), file)) {
        if (current_line == n) {
            fclose(file);
            line[strcspn(line, "\n")] = '\0';
            return line;
        }
        current_line++;
    }

    fclose(file);
    return NULL; 
}
