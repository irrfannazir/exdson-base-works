#include "../data.h"
#include "print.h"
#include "tree_node.h"
#include "tree_least_priority.h"
// #include "debug.h"
// #include "../include/tree.h"
// #include "../include/tree_least_priority.h"
// #include "../include/tree_node.h"
// #include "../include/expression.h"
// #include "../include/print.h"
#include "../include/debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FUNCTION_ARGUMENT_LIMIT 50


char *function_id[FUNCTION_MAX] = {"pow"};
int function_len[FUNCTION_MAX] = {2};
int function_size = 1;



int find_the_function(struct Node *ptr){
    for(int i = 0; i < function_size; i++){
        if(
            strcmp(token[ptr -> start], function_id[i]) == 0
                &&
            strcmp(token[ptr -> start + 1], "(") == 0
                &&
            strcmp(token[ptr -> start + ptr -> size - 1], ")") == 0
        ){
            (!ismath && (i == 0)) ? (ismath = 1) : (0);
            return i;
        }
    }
    return -1;
}

int analyze_expression(struct Node *root){
    struct Node *ptr = find_next_expression(root);
    int j = 0;
    while(ptr != NULL){
        int isoperation = find_the_least_priority(ptr -> start, ptr -> size);
        int isunary = find_the_unary(ptr -> start, ptr -> size);
        int isfunction = find_the_function(ptr);
        if(
            isoperation == -1
            &&
            strcmp(token[ptr -> start], "(") == 0
            &&
            strcmp(token[ptr -> start + ptr -> size - 1], ")") == 0
        ){
            
            ptr -> start++;
            ptr -> size -= 2;
            ptr = find_next_expression(root);
            continue;
            
        }
        if(isfunction != -1){

            struct Node *ptr2 = ptr;
            int count = 0;
            int comma_found[FUNCTION_ARGUMENT_LIMIT];
            int end = ptr2 -> start + ptr2 -> size - 1;
            int isfunctionFound = 0;
            ptr -> right = createNode(FUNCTION_ARGUMENTS, ptr -> start, 1);
            for (int i = ptr -> start + 2; i < ptr -> start + ptr -> size -1 && i < sizeof(token) / sizeof(token[0]); i++) {
                if (strcmp(",", token[i]) == 0 && !isfunctionFound) {
                    comma_found[count] = i;
                    count++;
                    if(count == FUNCTION_ARGUMENT_LIMIT){
                        printf("The arguments of the function %s is maximum.\n", token[ptr -> start]);
                        exit(1);
                    }
                }else if(strcmp("(", token[i]) == 0){
                    isfunctionFound = 1;
                }else if(strcmp(")", token[i]) == 0){
                    isfunctionFound = 0;
                }
            }
            if(count + 1 > function_len[isfunction]){
                printe("The unexpected argument.", ptr -> start, 0);
                printf("\t\t%s have only %d argument.\n", function_id[isfunction], function_len[isfunction]);
                return 0;
            }else if(count + 1 < function_len[isfunction]){
                printe("The expected argument.", ptr -> start, 0);
                printf("\t\t%s have atleast %d argument.\n", function_id[isfunction], function_len[isfunction]);
            }

            #ifdef DEBUG_FUNCTION_ARGUMENTS
              printf("Count of comma seperation: %d\n", count);
              printf("Arguments in the functions\n");
            #endif
            
            if(count == 0){

                ptr2 -> left = createNode(UNARY_EXPRESSION, ptr -> start + 2, ptr -> size - 3);
                PRINT_TOKENS_FOR_DEBUG(ptr -> start + 2, ptr -> start + ptr -> size - 1);

            }
            while(count > 0){
                
                ptr2 -> left = createNode(FUNCTION_ARGUMENTS, -1, -1);
                ptr2 = ptr2 -> left;
                count--;
                ptr2 -> right = createNode(UNARY_EXPRESSION, comma_found[count] + 1, end - comma_found[count] - 1);
                end = comma_found[count];
                PRINT_TOKENS_FOR_DEBUG(comma_found[count] + 1, end);

            }
            ptr2 -> left = createNode(UNARY_EXPRESSION, ptr -> start + 2, end - ptr -> start - 2);
            PRINT_TOKENS_FOR_DEBUG(ptr -> start + 2, end);
        }else if(isoperation != -1){
            ptr -> right = createNode(OPERATOR, isoperation, 1);
            //Operator
            ptr -> left = createNode(BINARY_EXPRESSION, -1, -1);
            // Binary
            ptr -> left -> left = createNode(UNARY_EXPRESSION, ptr -> start, isoperation - ptr -> start);
            ptr -> left -> right = createNode(UNARY_EXPRESSION, isoperation + 1, ptr -> size + ptr -> start - isoperation - 1);
            // printf(":: %d\n", a - ptr -> size);
            ptr = ptr -> left;
        }else if(isunary != -1){
            ptr -> right = createNode(OPERATOR, ptr -> start, 1);
            if(isunary == 1){
                ptr -> left = createNode(UNARY_EXPRESSION, ptr -> start + 1, ptr -> size - 1);
            }else if(isunary == 2){
                ptr -> left = createNode(UNARY_EXPRESSION, ptr -> start + 2, ptr -> size - 3);
            }
            // ptr = ptr -> left;
        }else{
            for(int i = ptr -> start; i < ptr -> start + ptr -> size; i++){
                printf("%s ", token[i]);
            }
            printf(" : is an Invalid expression.\n");
            return 0;
        }
        ptr = find_next_expression(root);
        j++;
    }
    root_array[line_size] = root;
    return 1;
}

int parsing_tree_expression(int index, int size){
    // Grammatical expression
    // 0: E -> E BOp E
    // 1: E -> UOp E
    // 2: E -> (E)
    // 3: E -> id(E, .., ..)
    struct Node *root = createNode(0, index, size); 
    int result = analyze_expression(root);
    if(result == 0){
        return 0;
    }

    #ifdef DISPLAY_POSTFIX
      display_postfix(root);
      #undef DISPLAY_POSTFIX
    #endif
    save_expression_root(root);
    return 1;
}