#include "../include/tree.h"
#include "../include/tree_least_priority.h"
#include "../include/tree_node.h"
#include "../data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *function_id[500] = {"f"};
int function_len[500] = {1};
int function_size = 1;



int isfunction(struct Node *ptr){
    for(int i = 0; i < function_size; i++){
        // printf("%d\t", ptr -> start);
        // printf("%d\n", ptr -> size);
        // display_token();
        // single a = 3+f(4, 6)#
        printf("function: %s %s %s\n", token[ptr -> start], token[ptr -> start + 1], token[(ptr -> start) + (ptr -> size) - 1]);
        if(
            strcmp(token[ptr -> start], function_id[i]) == 0
                &&
            strcmp(token[ptr -> start + 1], "(") == 0
                &&
            strcmp(token[ptr -> start + ptr -> size - 1], ")") == 0
        ){
            return i;
        }
    }
    return -1;
}

int exp_analysing(struct Node *root){
    struct Node *ptr = find_the_exp(root);
    int j = 0;
    while(ptr != NULL){
        int a = find_the_least_priority(ptr -> start, ptr -> size);
        printf("%d\n", a);
        if(isfunction(ptr) != -1){
            ptr -> right = createNode(5, ptr -> start, 1);
            struct Node *ptr2 = ptr;
            int count = 0;
            int comma_found[MAX];
            int end = ptr2 -> start + ptr2 -> size - 1;
            for (int i = ptr -> start + 2; i < ptr -> start + ptr -> size -1 && i < sizeof(token) / sizeof(token[0]); i++) {
                if (strcmp(",", token[i]) == 0) {
                    comma_found[count] = i;
                    count++;
                }
            }
            ptr2 -> right = createNode(5, ptr -> start, 1);
            while(count > 0){
                ptr2 -> left = createNode(5, -1, -1);
                ptr2 = ptr2 -> left;
                count--;
                ptr2 -> right = createNode(0, comma_found[count] + 1, end - comma_found[count] - 1);
                // printf("%d:%d\n", ptr -> start + 2, comma_found[count]);
                end = comma_found[count];
            }
            ptr2 -> left = createNode(0, ptr -> start + 2, end - ptr -> start - 2);
        }else if(a != -1){
            ptr -> right = createNode(2, a, 1);
            //Operator
            ptr -> left = createNode(1, -1, -1);
            // Binary
            ptr -> left -> left = createNode(0, ptr -> start, a - ptr -> start);
            ptr -> left -> right = createNode(0, a + 1, ptr -> size + ptr -> start - a - 1);
            // printf(":: %d\n", a - ptr -> size);
            ptr = ptr -> left;
        }else{
            printf("invalid expression.\n");
            return 0;
        }
        ptr = find_the_exp(ptr);
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
    int a = exp_analysing(root);
    if(a == 0){
        return 0;
    }
    // display_postfix(root);
    add_the_root(root);
    return 1;
}