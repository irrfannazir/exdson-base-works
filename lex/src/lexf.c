#include "../data.h"
#include <stdio.h>

/* FAULTS AND IMPROVEMENTS NEEDED:
 * 
 * 1. No buffer overflow checks:
 *    - append_token_to_file() doesn't verify token length before writing.
 *    - Risk of buffer overflow if token is too large for file line.
 * 
 * 2. No file operation atomicity:
 *    - If program crashes mid-write, files may be corrupted.
 *    - Consider write-to-temp-then-rename pattern for critical files.
 * 
 * 3. Missing input validation:
 *    - No NULL checks for filename parameters.
 *    - No validation of type values in append_token_to_file().
 * 
 * 4. No file permission checks:
 *    - Don't verify if file is actually writable before operations.
 * 
 */


int append_indent_to_file(const char *filename, int indent) {
    
    FILE *file = fopen(filename, "a");
    if (!file){
        __pc_error__("Error while appending indent data to list file named %s", filename);
        fclose(file);
        return 1;
    }
    
    fprintf(file, "-1 %d\n", indent);

    fclose(file);
    return 0;
}

int append_token_to_file(const char *filename, t_type type, char *token) {
    FILE *file = fopen(filename, "a");
    if (!file){
        __pc_error__("Error while appending token data to list file named %s", filename);
        fclose(file);
        return 1;
    }

    fprintf(file, "%d %s\n", type, token);

    fclose(file);
    return 0;
}

int clear_file(const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file){
        __pc_error__("Error while clearing file named %s", filename);
        fclose(file);
        return 1;
    }

    
    fclose(file);
    return 0;
}

