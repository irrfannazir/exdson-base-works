#include <stdio.h>

int dfa_new_token(const char *filename, t_type value){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file for concatenation.\n");
        return 1;
    }
    fprintf(fp, " %d\n", value);
    fclose(fp);
}

int dfa_string_conc(const char *filename, char c){
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file for concatenation.\n");
        return 1;
    }
    fputc(c, fp);
    fclose(fp);
}