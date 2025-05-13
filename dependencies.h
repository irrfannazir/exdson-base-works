#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#define COMPILER_C
// #define READ_FROM_INPUT
#ifndef READ_FROM_INPUT
  #define READING_FILE_DIRECTORY "./main.ex"
#endif




// #define DEBUG_MODE
// #define DISPLAY_TOKEN
// #define DATATYPE_DISPLAY
// #define ARRAY_SYNTAX_CHECK
// #define SYNTAX_INFO
// #define DISPLAY_POSTFIX
#ifdef DEBUG_MODE
  #ifndef DISPLAY_TOKEN 
    #define DISPLAY_TOKEN
  #endif
  #ifndef DATATYPE_DISPLAY
    #define DATATYPE_DISPLAY
  #endif
#endif


#endif