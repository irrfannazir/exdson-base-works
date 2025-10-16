#ifndef DATA_H
#define DATA_H
#include "lex/include/filename.h"
#include "utils/p_error.h"
/*
    This is the file where all the data which is commonly used for lex, parse, compile.
*/




//limits
#define TOKEN_STRING_MAX 50
#define TOKEN_SIZE_MAX 500
#define DATATYPE_INPUT_LENGTH 75
#define DATATYPE_INPUT_ARRAY_SIZE 5
#define DATATYPE_SIZE_MAX 500
#define DATATYPE_NAME_SIZE_MAX 50
#define LINE_MAX 500
#define PARAMETRE_MAX 20
#define FUNCTION_MAX 500
#define PARAMETRE_PROGRAM_TEMP_MAX 500
#define PROGRAM_TEMP_MAX 4*PARAMETRE_PROGRAM_TEMP_MAX

#define DIRECTORY_MAX_SIZE 1024
#define PARSING_HANDLING_FILE_NAME "parse.txt"
#define PGM_EXATED_FILE_NAME "program.c"


#define DIGIT 20
#define STRING_MAX (DIGIT+TOKEN_STRING_MAX+1)


// parse
#define PARSE_DATATYPE_LIST_FILE_NAME "grammar/t_stat.txt"





typedef enum{
    TOKEN_EOF,          // 0 End Of File
    TOKEN_IDENTIFIER,   // 1 Identifiers (variables, function names, etc.)
    TOKEN_INTEGER,      // 2 Integer literals (e.g., 123, 456)
    TOKEN_KEYWORD,      // 3 Keywords (e.g., if, for, while, etc.)
    TOKEN_OPERATOR,     // 4 Operators (e.g., +, -, *, /, ==)
    TOKEN_PUNCTUATION,  // 5 Punctuation (e.g., (, ), {, }, ;, ,)
    TOKEN_DATATYPE,     // 6 Datatypes (e.g., int, float, char)
    TOKEN_EXPRESSION,   // 7 Expressions (e.g., arithmetic, logical)
    TOKEN_STRING,       // 8 String literals (e.g., "Hello")
    TOKEN_NULL          // 9 Null Terminator
} t_type;


//lexical
extern t_type type[TOKEN_SIZE_MAX];
extern int token_size;
extern int total_error;
// extern char datatypes[DATATYPE_SIZE_MAX][DATATYPE_NAME_SIZE_MAX];
// extern char datatype_input[DATATYPE_SIZE_MAX][DATATYPE_INPUT_ARRAY_SIZE][DATATYPE_INPUT_LENGTH];
extern int datatype_size;

//parse
extern int dont_compile;
extern int line_method[LINE_MAX];
extern int line_size;
extern int parametre_list[LINE_MAX][PARAMETRE_MAX];
extern char *function_id[FUNCTION_MAX];
extern int function_len[FUNCTION_MAX];
extern int function_size;

//compile
extern int ismath;


//functions
int num_lines(int size);
void display_token();
int get_indentation(int index);
char *get_token(int index);
t_type get_type(int index);
void get_type_token(int index, t_type *type, char str[TOKEN_STRING_MAX]);




#endif
