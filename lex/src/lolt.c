#include <stdio.h>
#include <string.h>
#include "lexh.h"
#include "dfah.h"

#define MAX_WORD_SIZE 256

int size_of_last_line(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char c;
    int size;
    while ((c = fgetc(fp)) != -1) {
        if (c == '\n'){
            size = 0;
        }else{
            size++;
        }
    }

    fclose(fp);
    return size + 2;
}

int fget_last_line(const char *filename, char *last_line, int size){
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char line[size];
    
    while (fgets(line, size, fp)) {
        strcpy(last_line, line);
    }

    fclose(fp);
    last_line[strcspn(last_line, "\n")] = '\0';

    return 0;
}

t_type lexeme_of_last_line(const char *filename) {

    int size = size_of_last_line(filename);
    if (size == 0) return TOKEN_EOF;
    char last_line[size];
    if (!fget_last_line(filename, last_line, size)){
        if (iskeyword(last_line)) return TOKEN_KEYWORD;
        if (isdatatype(last_line)) return TOKEN_DATATYPE;
    }

    return TOKEN_IDENTIFIER;
}