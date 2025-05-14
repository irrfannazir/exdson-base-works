#include "../dependencies.h"

// #define DEBUG_PARSE
#ifdef DEBUG_PARSE
 #ifndef DEBUG_H
  #define DEBUG_H
  
  void debug_the_false_arg(int count, ...);
  void debug_the_tokens(char *comment, int index, int size);
 
 
  // #define DISPLAY_POSTFIX
  // #define ARRAY_SYNTAX_CHECK
  
  // #define DEBUG_FUNCTION_ARGUMENTS
  #ifdef DEBUG_FUNCTION_ARGUMENTS
   #define PRINT_TOKENS_FOR_DEBUG(START, END)                                 \
    //To print the tokens of from START to END
    for(int __tokens_var__ = START; __tokens_var__ < END; __tokens_var__++){  \
      printf("%s ", token[__tokens_var__]);                                   \
    }                                                                         \
    printf("\n");
  #endif
 

  // #define SEGMENTATION_FAULT
  #ifdef SEGMENTATION_FAULT
   //Check the bounds out of the LIMIT
   #define DEBUG_SEG_FAULT(VAR, LIMIT, MSG) \
    if(VAR >= LIMIT){                       \
      printf(MSG);                          \
      exit(1);                              \
    }
   #undef SEGMENTATION_FAULT
  #endif

  #define PRINT_ARRAY_FROM_TOKEN
  #ifdef PRINT_ARRAY_FROM_TOKEN
   #define PRINT_TOKEN(COMMENT, INDEX) \
    printf("COMMENT: %s\t", token[INDEX]);
   #undef PRINT_ARRAY_FROM_TOKEN
  #endif
 #endif
#endif


#ifndef PRINT_TOKENS_FOR_DEBUG
 #define PRINT_TOKENS_FOR_DEBUG(START, END)
#endif
#ifndef DEBUG_SEG_FAULT
 #define DEBUG_SEG_FAULT(VAR, LIMIT, MSG)
#endif
#ifndef PRINT_TOKEN
 #define PRINT_TOKEN
#endif

