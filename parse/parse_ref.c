#include "../data.h"
#include <stdio.h>
#include <string.h>

int dont_compile = 0;

int buffer_start = -1;
int buffer_end = -1;
int bracket_start = -1;
int bracket_end = -1;

int line_model[MAX];
int line_size = 0;
char buffer[MAX][MAX];
int buffer_size = 0;

int isbuffer(){
    return (buffer_start != -1) && (buffer_end != -1);
}
int isbracket(){
    return (bracket_start != -1) && (bracket_end != -1);
}

void analyze_punctuator(int index){
    if(strcmp(token[index], "<") == 0){
        buffer_start = index;
    }else if(strcmp(token[index], ">") == 0){
        buffer_end = index;
    }else if(strcmp(token[index], "(")== 0){
        bracket_start = index;
    }else if(strcmp(token[index], ")") == 0){
        bracket_end = index;
    }
}

void printe(char *str){
    printf("Error: ");
    printf(str);
    if(dont_compile == 0){
        dont_compile = 1;
    }
    printf("\n");
}

void printw(char *str){
    printf("Warning: ");
    printf(str);
    printf("\n");
}

// int declare_the_var_with_buffer(int index, int size){
//     // if(
//     //     (type[index] == t_datatype)
//     //      &&
//     //     (isbuffer())
//     // ){
//     //     if(buffer_end + 1 < size && (size - buffer_end)%2 == 0 && type[buffer_end + 1] != t_identifier){
//     //         printf("The %s is declared with name.\n", token[index]);
//     //         return -2;
//     //     }else if(buffer_end + 1 < size){
//     //         int next = 0;
//     //         for(int i = buffer_end; i < size; i++){
//     //             if(type[i] == t_identifier){
//     //                 if(next == 1){
//     //                     printe("Expeted , before identifier.\n");
//     //                     return -2;
//     //                 }
//     //                 next = 1;
//     //             }else if(token[i][0] == ','){
//     //                 if(next == 0){
//     //                     printe("Expeted identifier after ,.\n");
//     //                     return -2;
//     //                 }
//     //                 next = 0;
//     //             }
//     //         }
//     //     }else if(buffer_end + 1 >= size){
//     //         printe("Expected identifier after datatype declaration.\n");
//     //     }else if(buffer_start+1 == buffer_end){
//     //         printw("The buffer is empty");
//     //     }
//     //     int next = 0;
//     //     for(int i = buffer_start; i < buffer_end; i++){
//     //         if(token[i][0] != ','){
//     //             if(type[i] == t_identifier || type[i] == t_integer){
//     //                 strcpy(buffer[MAX], token[i]);
//     //             }else{
//     //                 printe("Expected identifier or value.\n");
//     //                 return -2;
//     //             }
//     //             next = 1;
//     //         }else if(next == 1){
//     //             next = 0;
//     //         }
//     //     }
//     //     if(next == 0){
//     //         printe("The expected expression after .\n");
//     //         return -2;
//     //     }
//     // }
//     // line_model[line_size] = 2;
//     // line_size++;
//     return 3;
// }

// int declare_default_var(int index, int size){
//     //single a
//     // if(
//     //     (type[index] == t_datatype)
//     //         &&
//     //     (type[index+1] == t_identifier)
//     //         &&
//     //     (!isbuffer())
//     // ){
//     //     printf("The %s has declared with name %s\n", token[index], token[index+1]);
//     //     return -1;
//     // }
//     line_model[line_size] = 1;
//     line_size++;
//     return 1;
// }

// int declare_the_var(int index, int size){
//     //single a = 3
//     // if(
//     //     (size > 3)
//     //      &&
//     //     (!isbuffer())
//     //      &&
//     //     (type[index] == t_datatype)
//     //      &&
//     //     (type[index+1] == t_identifier)
//     //      &&
//     //     (strcmp(token[index+2], "=") == 0)
//     // ){
//     //     if(type[index + 3] == t_integer){
//     //         printf("The %s is decalred with name %s and value %s.\n", token[index], token[index+1], token[index+3]);
//     //     }else{
//     //         printe("Yet not developed");
//     //     }
//     // }else if(
//     //     (size > 3)
//     //      &&
//     //     (!isbuffer())
//     //      &&
//     //     (type[index] == t_datatype)
//     //      &&
//     //     (type[index+1] == t_identifier)
//     // ){
//     //     printe("Expected = after identifier.\n");
//     //     return -1;
//     // }
//     line_model[line_size] = 0;
//     line_size++;
//     return 2;
// }

int declare_default_var(int index, int size){
    if(
        // single a
        (type[index] == t_datatype)
            &&
        (type[index+1] == t_identifier)
            &&
        (!isbuffer())
            &&
        (size == 2)
    ){
        printf("The %s has declared with the name of %s", token[index], token[index+1]);
        return -1;
    }
    return 1;
}

void parse_the_line(int index, int size){
    int k = 0;
    while(k >= 0){
        switch(k){
            case 0:
                // k = declare_default_var(index, size);
                break;
            case 1:
                // k = declare_the_var(index, size);
                break;
            case 2:
                // k = declare_the_var_with_buffer(index, size);
                break;
            case 3:
                printe("Invalid Syntax!");
                k = -1;
                break;
        }
    }
}

void parsef(){
    int i = 0;
    int j = 0;
    while(i + j < token_size){
        if(type[i+j] == t_punctuation){
            analyze_punctuator(i+j);
        }
        if(type[i+j] == t_eof){
            parse_the_line(i, j);
            i = i+j+1;
            j = 0;
        }else{
            j++;
        }
    }
    return;
}