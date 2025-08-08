#include "../data.h"
#include <stdio.h>

/* FAULTS AND IMPROVEMENTS NEEDED:
 * 
 * 1. append_indent_to_file() and append_token_to_file() have duplicate error handling.
 *    - Consider creating a helper function for file opening with error handling.
 * 
 * 2. No buffer overflow checks:
 *    - append_token_to_file() doesn't verify token length before writing.
 *    - Risk of buffer overflow if token is too large for file line.
 * 
 * 3. Inconsistent error handling:
 *    - append_* functions return -1 on error, but clear_file() returns void.
 *    - Standardize return types (e.g., all return int for consistency).
 * 
 * 4. clear_file() writes a space instead of truly clearing:
 *    - fopen() with "w" mode already truncates, so fprintf is redundant.
 *    - If goal is truly empty file, just open/close with "w" mode.
 * 
 * 5. No file operation atomicity:
 *    - If program crashes mid-write, files may be corrupted.
 *    - Consider write-to-temp-then-rename pattern for critical files.
 * 
 * 6. Missing input validation:
 *    - No NULL checks for filename parameters.
 *    - No validation of type values in append_token_to_file().
 * 
 * 7. Resource leak risk:
 *    - If fprintf() fails between fopen() and fclose(), file handle leaks.
 *    - Consider using goto error handling or scope guards.
 * 
 * 8. Magic numbers:
 *    - "-1" in append_indent_to_file() should be a named constant.
 * 
 * 9. No file permission checks:
 *    - Don't verify if file is actually writable before operations.
 * 
 * 10. Cross-platform issues:
 *    - Line endings (\n) may need adjustment for Windows (\r\n).
 */


int append_indent_to_file(const char *filename, int indent) {
    
    FILE *file = fopen(filename, "a");
    if (!file){
        __pc_error__("Error while appending indent data to list file named %s", filename);
        return -1;
    }
    
    fprintf(file, "-1 %d\n", indent);

    fclose(file);
    return 0;
}

int append_token_to_file(const char *filename, t_type type, char *token) {
    FILE *file = fopen(filename, "a");
    if (!file){
        __pc_error__("Error while appending token data to list file named %s", filename);
        return -1;
    }

    fprintf(file, "%d %s\n", type, token);

    fclose(file);
    return 0;
}

void clear_file(const char *filename){
    FILE *file = fopen(filename, "w");
    if (!file){
        __pc_error__("Error while clearing file named %s", filename);
        return;
    }

    fprintf(file, " ");

    fclose(file);
}

