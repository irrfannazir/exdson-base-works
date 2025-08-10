#include "../include/file_utils.h"
#include "../alt-parse/include/strh.h"
#include <sys/stat.h>

static bool file_exists(const char* filename) {
    struct stat st;
    return stat(filename, &st) == 0;
}

char* get_nth_line(const char* filename, int n, const char *keyword, int countcolon) {
    if (!file_exists(filename)) return NULL;

    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int current_line = 0;
    char* result = NULL;
    if(keyword != NULL){
        while((read = getline(&line, &len, file)) != -1){
            int line_len = strlen(line);
            if(line[line_len - 1] == '\n' && line[line_len - 2] == ':'){
                line[line_len - 2] = '\0'; 
            }else if(line[line_len - 1] == '\n'){
                line[line_len - 1] = '\0'; 
            }
            if(strcmp(line, keyword) == 0){
                // printf("Checking keyword %s and %s\n", line, keyword);
                break;
            }
        }
    }

    while ((read = getline(&line, &len, file)) != -1) {
        if (current_line == n) {
            result = strdup(line);
            break;
        }
        if(countcolon){
            int line_len = strlen(line);
            if(line[line_len - 2] == ':'){
                current_line++;
            }
            if(current_line == n){
                line[line_len - 2] = '\0';
                result = strdup(line);
                return result;
            }
        }else{
            current_line++;
        }
    }

    free(line);
    fclose(file);
    return result;
}