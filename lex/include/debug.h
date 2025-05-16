
#define DEBUG_LEX
#ifdef DEBUG_LEX
 #ifndef DEBUG_H
 #define DEBUG_H
//   #define DISPLAY_TOKEN
//   #define DATATYPE_DISPLAY
  #ifdef DATATYPE_DISPLAY
    #define DISPLAY_DATATYPE_LIST                                                                \
        printf("Datatype List:\n");                                                                     \
        for (int i = 0; i < datatype_size; i++) {                                                       \
            printf("%s\n", datatypes[i]);                                                               \
        }                                                                                               \
        printf("\nDatatype Input List:\n");                                                             \
        for (int i = 0; i < datatype_size; i++) {                                                       \
            for (int j = 0; j < DATATYPE_INPUT_ARRAY_SIZE && datatype_input[i][j][0] != '\0'; j++) {    \
                printf("%s ", datatype_input[i][j]);                                                    \
            }                                                                                           \
            printf("\n");                                                                               \
        }                                                                                               \
        printf("\n");                                                                                   \
        }
 #endif
  
 #endif
#endif

#ifndef DISPLAY_DATATYPE_LIST
 #define DISPLAY_DATATYPE_LIST
#endif
