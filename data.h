#ifndef DATA_H
#define DATA_H
#include "lex/include/dfah.h"
#include "lex/include/filename.h"
#include "include/pc_error.h"
#include "include/constants.h"
/*
    This is the file where all the data which is commonly used for lex, parse, compile.
*/




//limits

#define TOKEN_STRING_MAX 500
#define DATATYPE_INPUT_LENGTH 75
#define DATATYPE_INPUT_ARRAY_SIZE 5
#define DATATYPE_SIZE_MAX 500
#define DATATYPE_NAME_SIZE_MAX 50
#define FUNCTION_MAX 500
#define PARAMETRE_PROGRAM_TEMP_MAX 500
#define PROGRAM_TEMP_MAX 4*PARAMETRE_PROGRAM_TEMP_MAX
#define DIRECTORY_MAX_SIZE 1024
#define NAME_STRLEN 1024


#define PARSING_HANDLING_FILE_NAME "parse.txt"
#define DEFINED_IDENTIFIER_FILE_NAME "name_identifier.txt"
#define PGM_EXATED_FILE_NAME "program.c"


#define DIGIT 20
#define STRING_MAX (DIGIT+TOKEN_STRING_MAX+1)


// parse
#define PARSE_DATATYPE_LIST_FILE_NAME "grammar/t_stat.txt"


// flush
#ifdef DELETE_UNWANTED_FILES
  static const char *unwanted_filenames[] = {
    "lex.txt",
    PARSING_HANDLING_FILE_NAME,
    PGM_EXATED_FILE_NAME,
    DEFINED_IDENTIFIER_FILE_NAME
};
#endif



//lexical
extern int token_size;
extern int total_error;
extern int datatype_size;

//parse
extern int dont_compile;
extern int line_size;
extern char *function_id[FUNCTION_MAX];
extern int function_len[FUNCTION_MAX];
extern int function_size;

//compile
extern int ismath;


//functions
int get_indentation(int index);
char *get_token(int index);
t_type get_type(int index);
void get_type_token(int index, t_type *type, char str[TOKEN_STRING_MAX]);




#endif
