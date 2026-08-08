#ifndef DATA_H
#define DATA_H
#include "lex/dfah.h"
#include "lex/lfn.h"
#include "common/constants.h"
/*
    This is the file where all the global data which is commonly used for lex, parse, compile.
*/


//limits
#define DIGIT 20
#define TOKEN_STRING_MAX 500
#define LEX_LINE_MAX TOKEN_STRING_MAX + DIGIT + 1
#define PARSE_LINE_MAX 1024
#define PSUEDO_CODE_MAX 1024

#define NAME_STRLEN 1024


//filename
#define GENERATED_DIRECTORY           "build"
#define PARSING_HANDLING_FILE_NAME    GENERATED_DIRECTORY "/parse.txt"
#define PGM_EXATED_FILE_NAME          GENERATED_DIRECTORY "/pgm.c"
#define PARSED_INFORMATION            GENERATED_DIRECTORY "/parse.info"
#define PARSE_DATATYPE_LIST_FILE_NAME "grammar/datatype.txt"
#define PARSE_KEYWORD_LIST_FILE_NAME  "grammar/keywords.bin"
#define IC_FILENAME                   GENERATED_DIRECTORY "/ic.orgex"


#define SYMTAB_FILE_NAME_FORMAT        GENERATED_DIRECTORY "/symtab_%03d.bin"
#define SYMTAB_FILE_NAME(buf, digit) snprintf((buf), (sizeof(SYMTAB_FILE_NAME_FORMAT)), SYMTAB_FILE_NAME_FORMAT, (digit))


// flush
#ifdef DELETE_UNWANTED_FILES
  static const char *unwanted_filenames[] = {
    "build/lex.txt",
    PARSING_HANDLING_FILE_NAME,
    PGM_EXATED_FILE_NAME,
    PARSED_INFORMATION,
    IC_FILENAME
  };
#endif
  
  

extern int dont_compile;


//functions
int get_indentation(int index);
char *get_token(int index);
t_type get_type(int index);
void get_type_token(int index, t_type *type, char str[TOKEN_STRING_MAX]);




#endif
