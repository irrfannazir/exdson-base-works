#ifndef DEBUG_H
#define DEBUG_H

void debug_the_token(char *comment, int index);
void debug_the_false_arg(int count, ...);
void debug_the_tokens(char *comment, int index, int size);


// #define DEBUG_FUNCTION_ARGUMENTS
// #define DISPLAY_POSTFIX
// #define DEBUG_MODE
#ifdef DEBUG_MODE
  #ifndef DISPLAY_POSTFIX
    #define DISPLAY_POSTFIX
  #endif
  #ifndef DEBUG_FUNCTION_ARGUMENTS
    #define DEBUG_FUNCTION_ARGUMENTS
  #endif
#endif

#ifdef DEBUG_FUNCTION_ARGUMENTS
  #define PRINT_TOKENS_FOR_DEBUG(START, END)                                  \
    for(int __tokens_var__ = START; __tokens_var__ < END; __tokens_var__++){  \
        printf("%s ", token[__tokens_var__]);                                 \
    }                                                                         \
    printf("\n");
#else
  #define PRINT_TOKENS_FOR_DEBUG(START, END)
#endif

// #define DEBUG_SEG_FAULT(VAR, LIMIT, MSG)  \
//   if(VAR >= LIMIT){                       \
//     printf(MSG);                          \
//     exit(1);                              \
//   }

#endif