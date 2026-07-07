#ifndef COMPILEH_H
#define COMPILEH_H

#define DEFAULT_PROGRAM "$$include_cursor; $$function_cursor;int main(){$$program_cursor;return 0;}"
#define PGM_CURSOR "$$program_cursor;"
#define FUNCTION_CURSOR "$$function_cursor;"
#define INCLUDE_CURSOR "$$include_cursor;"
#define C_PROGRAM_MAX 500

typedef enum {
    INSTRUCTION_DECLARATION = 0,
    INSTRUCTION_DECLARATION_WITHOUT_ASSIGNMENT = 1,
    INSTRUCTION_ASSIGNMENT = 2,
    INSTRUCTION_IF_BLOCK = 3,
    INSTRUCTION_ELSE_IF_BLOCK = 4,
    INSTRUCTION_ELSE_BLOCK = 5,
    INSTRUCTION_FOR_BLOCK = 6,
    INSTRUCTION_WHILE_BLOCK = 7,
    INSTRUCTION_PRINT = 8
} InstructionKind;

int *line_to_int_array(const char *line, int *count);
int compile_file(const char *filename);
void add_the_header(const char *filename, const char *headername);
char *serialize(int start, int end);
void remove_string_from_file(const char *filename, const char *target, int isloop);
const char *find_datatype(int index);

void declaration_exec(const char *dfn, int *arr, int count);
void assign_exec(const char *dfn, int *arr, int count);
void block_paradigm(const char *dfn, char *keyword, int *arr, int count);
void else_condition(const char *dfn);
void for_condition(const char *dfn, int *arr, int count);
void print_statement(const char *dfn, int *arr, int count);

#endif
