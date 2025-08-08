#include "tree.h"
#include "syntax.h"
#include "parseh.h"
#include <stdio.h>
#include <string.h>
#include "../data.h"


int count_nos(char *line){
    int count = 0;
    int tn = 0;
    char *st = tokenize_white_space(line, tn);
    tn++;
    while(st != NULL){
        if(does_tree_needed(st)){
            count++;
        }
        st = tokenize_white_space(line, tn);
        tn++;
    }
    return count;
}

int check_line(struct Node *ptr, char *syn_line){
    int tn = 0;
    int nos = count_nos(syn_line);
    int ci = ptr->start;
    char *word = tokenize_white_space(syn_line, tn++);
    while(word != NULL){
        if(does_tree_needed(word)){
            char *end = tokenize_white_space(syn_line, tn++);
            if(end != NULL){
                while(!compare_the_word(end, get_token(ci)) && ci < ptr->start + ptr->size){
                    ci++;
                }
                if(ci == ptr->start + ptr->size){
                    return 1;
                }
                if(nos == 3){
                    if(ptr -> right != NULL){
                        ptr -> right -> left = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
                        ptr -> right -> right = createNode(NULL, EXPRESSION, ci + 1, -1);
                    }else{
                        ptr -> left = createNode(strdup(word), EXPRESSION, ptr -> start, ci - ptr -> start);
                        ptr -> right = createNode(NULL, BINARY_EXPRESSION, -1, -1);
                        ci--;
                    }
                }
                else if(nos == 2){
                    ptr->left = createNode(NULL, OPERATOR, ci, 1);
                    ptr->right = createNode(NULL, BINARY_EXPRESSION, -1, -1);
                    ptr->right->left = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
                    ptr->right->right = createNode(NULL, EXPRESSION, ci + 1, (ptr->start + ptr->size) - (ci + 1));
                }
            } else {
                if(ptr->right && ptr->right->right){
                    if(nos == 3){
                        ptr -> right -> right -> format = strdup(word);
                        ptr -> right -> right -> size = (ptr->start + ptr->size) - ptr -> right -> right -> start;
                    }else if(nos == 2){
                        ptr->right->right->format = strdup(word);
                        ptr->right->right->size = (ptr->start + ptr->size) - ptr->right->right->start;
                    }
                }
                
            }
        } else if (!compare_the_word(word, get_token(ci))) {
            return 1;
        }

        word = tokenize_white_space(syn_line, tn++);
        ci++;
    }

    return 0; 
}

int analyze_expression(struct Node *ptr){
    // Go through each line from syntax.txt
    int ln = 0;
    char *syn_line = get_line_from_syntax(ptr -> format, ln);
    ln++;
    while(syn_line != NULL){
        int status;
        status = check_line(ptr, syn_line);
        if(status){
            syn_line = get_line_from_syntax(ptr -> format, ln);
            ln++;
        }else{
            free(syn_line);
            return 0;
        }
    }
    free(syn_line);
    return 1;
}
