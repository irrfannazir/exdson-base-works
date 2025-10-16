#include "file_utils.h"
#include <sys/stat.h>

#define MAX_WORD_LENGTH 256
#define MAX_LINE_LENGTH MAX_WORD_LENGTH*10
#define TEMP_FILE "temp_file.tmp"

static bool file_exists(const char* filename) {
    struct stat st;
    return stat(filename, &st) == 0;
}

void print_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
}

void remove_string(const char* filename, const char* target, bool is_loop) {
    if (!file_exists(filename)) return;

    FILE* original = fopen(filename, "r");
    FILE* temp = fopen(TEMP_FILE, "w");
    
    if (original && temp) {
        char line[MAX_LINE_LENGTH];
        bool changed;
        
        do {
            changed = false;
            rewind(original);
            rewind(temp);
            
            while (fgets(line, sizeof(line), original)) {
                char* pos = strstr(line, target);
                if (pos) {
                    changed = true;
                    size_t before_len = pos - line;
                    char new_line[MAX_LINE_LENGTH];
                    strncpy(new_line, line, before_len);
                    strcpy(new_line + before_len, pos + strlen(target));
                    fputs(new_line, temp);
                } else {
                    fputs(line, temp);
                }
            }
            
            if (!is_loop) break;
        } while (changed);
        
        fclose(original);
        fclose(temp);
        
        remove(filename);
        rename(TEMP_FILE, filename);
    }
}


