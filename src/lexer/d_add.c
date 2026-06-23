#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common/pc_error.h"
#include "data.h"



int fputs_with_newl(const char *filename, const char *str) {
    if (str == NULL || str[0] == '\0') return 0;
    FILE *fp = fopen(filename, "a");
    if ( !fp) {
        __pc_error__("Error while appending datatype to list file named %s", filename);
        return 1;
    }
    fprintf(fp, "%s\n", str);
    fclose(fp);
    return 0;
}

char* fgets_by_nth_line(const char *filename, int n){
    FILE *fp = fopen(filename, "r");
    if ( !fp) {
        __pc_error__("Error while retrieving datatype from list file named %s", filename);
        return NULL;
    }

    static char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (count == n) {
            
            line[strcspn(line, "\n")] = '\0';
            fclose(fp);
            return line;
        }
        count++;
    }

    fclose(fp);
    return NULL;
}

