#include <stdio.h>
#include <string.h>
#include "../data.h"

t_type lexeme_of_last_line(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return TOKEN_IDENTIFIER;
    }

    char line[256];
    char last_line[256];

    while (fgets(line, sizeof(line), fp)) {
        strcpy(last_line, line);
    }
    fclose(fp);

    last_line[strcspn(last_line, "\n")] = '\0';

    const char *keywords[] = {"if", "else", "elif", "new"};
    for (int i = 0; i < sizeof(keywords)/ sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], last_line) == 0)
            return TOKEN_KEYWORD;
    }

    fp = fopen(PARSE_DATATYPE_LIST_FILE_NAME, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return TOKEN_IDENTIFIER;
    }
    
    char name[256];
    
    while (fgets(name, sizeof(name), fp)) {
        name[strcspn(name, "\n")] = '\0';
        
        if (strcmp(name, last_line) == 0)
            return TOKEN_DATATYPE;
    }

    fclose(fp);
    return TOKEN_IDENTIFIER;
}