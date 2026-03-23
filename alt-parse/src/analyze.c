#include "tree.h"
#include "syntax.h"
#include "parseh.h"
#include "strh.h"
#include <stdio.h>
#include <string.h>
#include "../data.h"
#include "../include/fileh.h"


int count_tree_needed_words(char *line){
    int count = 0;
    char *copy = strdup(line);
    if (!copy) return 0;
    
    char *token = strtok(copy, " \t\n");
    while(token != NULL){
        if(does_tree_needed(token)){
            count++;
        }
        token = strtok(NULL, " \t\n");
    }    
    free(copy);
    return count;
}

int handle_tertiary_op(struct Node *ptr, char *word, int ci) {
    if (ptr->right != NULL) {
        ptr->right->right = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
        ptr->right->left = createNode(NULL, EXPRESSION, ci + 1, -1);
    } else {
        ptr->left = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
        ptr->right = createNode(NULL, BINARY_EXPRESSION, -1, -1);
        ci--;
    }
    return ci;
}

void handle_binary_op(struct Node *ptr, char *word, int ci) {
    ptr->left = createNode(NULL, OPERATOR, ci, 1);
    ptr->right = createNode(NULL, BINARY_EXPRESSION, -1, -1);
    ptr->right->right = createNode(strdup(word), EXPRESSION, ptr->start, ci - ptr->start);
    ptr->right->left = createNode(NULL, EXPRESSION, ci + 1,
        (ptr->start + ptr->size) - (ci + 1));
}

void assign_last_word(struct Node *ptr, char *word, int nos) {
    if (ptr->right && ptr->right->right) {
        if (nos == 3) {
            ptr->right->left->format = strdup(word);
            ptr->right->left->size =
                (ptr->start + ptr->size) - ptr->right->left->start;
        } else if (nos == 2) {
            ptr->right->left->format = strdup(word);
            ptr->right->left->size =
                (ptr->start + ptr->size) - ptr->right->left->start;
        }
    }
}

int find_matching_token(int ci, struct Node *ptr, char *end) {
    while (!compare_the_word(end, get_token(ci)) &&
           ci < ptr->start + ptr->size) {
        ci++;
    }
    return ci;
}

int check_line(struct Node *ptr, char *syn_line) {
    int tn = 0;
    int nos = count_tree_needed_words(syn_line);
    int ci = ptr->start;

    char *word = tokenize_white_space(syn_line, tn++);

    while (word != NULL) {

        if (does_tree_needed(word)) {
            char *end = tokenize_white_space(syn_line, tn++);
            if (end != NULL) {

                ci = find_matching_token(ci, ptr, end);
                if (ci == ptr->start + ptr->size) return 1;
                switch (nos){
                    case 3:
                        ci = handle_tertiary_op(ptr, word, ci);
                        break;
                    case 2:
                        handle_binary_op(ptr, word, ci);
                        break;
                }

            } else {
                assign_last_word(ptr, word, nos);
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
    char *syn_line = get_nth_line(SYNTAX_DIRECTORY, ln, ptr -> format);
    char *inline_function = strdup("");
    ln++;
    while(syn_line != NULL){
        int status;
        status = check_line(ptr, syn_line);
        if(status){
            syn_line = get_nth_line(SYNTAX_DIRECTORY, ln, ptr -> format);
            ln++;
        }else{
            free(syn_line);
            return 0;
        }
    }
    free(syn_line);
    return 1;
}
