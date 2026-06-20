#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/tree.h"
#include "parse/parseState.h"
#include "common/errorm.h"
#include "data.h"
#include "parse/pdebug.h"

#ifdef DISPLAY_TREE
    void displayTree(struct Node *root) {
        if (root == NULL) {
            return;
        }
        
        if(root -> left == NULL && root -> right == NULL){
            if(root -> var != NULL) {
                printf("%s ", root -> var);
                return;
            }
            for(int i = root -> start ; i < root -> start + root -> size; i++){
                printf("%s ", get_token(i));
            }
            // printf("\n");
        }
        displayTree(root->right);
        displayTree(root->left);
    }
#endif

void printNode(FILE *fh, struct Node *ptr){
    if(ptr -> var){
        fprintf(fh, "%s ", ptr -> var);
        free(ptr -> var);
    }else{
        for(int i = ptr -> start ; i < ptr -> start + ptr -> size; i++){
            fprintf(fh, "%s ", get_token(i));
        }
    }
}

static inline void shrink_the_tree(int *reg_avail, struct Node *root){
    if (root == NULL) {
        return;
    }

    #define NODE_LEFT           root -> left
    #define NODE_RIGHT          root -> right
    #define NODE_RIGHT_RIGHT    root -> right -> right
    #define NODE_RIGHT_LEFT     root -> right -> left

    if(
        root -> size == 1
    ){
        FILE *fh = fopen(IC_FILENAME, "a");
        fprintf(fh, "t%d = %s; ", *reg_avail, get_token(root -> start));
        fclose(fh);
        return;
    }
    
    if(NODE_RIGHT) shrink_the_tree(reg_avail, root->right);
    if(NODE_LEFT) shrink_the_tree(reg_avail, root->left);

    if(
        NODE_LEFT           == NULL ||
        NODE_RIGHT          == NULL ||
        NODE_RIGHT_RIGHT    == NULL ||
        NODE_RIGHT_LEFT     == NULL
    ) return;

    if(
        NODE_LEFT -> type           == OPERATOR &&
        NODE_RIGHT -> type          == BINARY_EXPRESSION &&
        NODE_RIGHT_RIGHT -> type    == EXPRESSION &&
        NODE_RIGHT_LEFT  -> type    == EXPRESSION
    ){
        FILE *fh = fopen(IC_FILENAME, "a");
        (*reg_avail)++;
        fprintf(fh, "t%d = ", *reg_avail);
        printNode(fh, NODE_RIGHT_RIGHT);
        printNode(fh, NODE_LEFT);
        printNode(fh, NODE_RIGHT_LEFT);
        fputs("; ", fh);
        fclose(fh);
    }else{ return; }
    
    freeNode(NODE_RIGHT);
    freeNode(NODE_LEFT);
    NODE_RIGHT = NULL;
    NODE_LEFT = NULL;
    root -> var = (char *)malloc(VAR_MAX * sizeof(char));
    sprintf(root -> var, "t%d", *reg_avail);

}

/*It is the where parsing tree in implemented*/
int parsing_tree_analysis(struct parseState *ps, char *format, int start, int size){
    struct Node *root = createNode(format, EXPRESSION, start, size);
    struct Node *ptr = find_next_expression(root);
    int endloop = 0;
    while(ptr != NULL && endloop < 20){
        #ifdef P_TREE_MODE
            puts("Checking: ");
            for(int i = ptr -> start; i < ptr -> start + ptr -> size; i++) printf("%s ", get_token(i));
            puts("\n");
        #endif
        int status = analyze_expression(ptr);
        #ifdef DISPLAY_TREE
            // displayTree(root); 
            // printf("\n\n");
        #endif
        if(status){
            char temp_exp[1024] = "";
            for(int i = start; i < start + size; i++){
                strcat(temp_exp, get_token(i));
            }
            pushError(ERROR_HANDLING_FILENAME, ps-> method_line_number, "%s is an invalid expression", temp_exp);
            dont_compile = 1;
            return 1;
        }
        ptr = find_next_expression(root);
        endloop++;
    }
    #ifdef DISPLAY_TREE
        displayTree(root);
        printf("\n\n");
    #endif
    shrink_the_tree(&(ps -> reg_avail), root);
    if(ps -> buffer) {
        sprintf(ps -> buffer, "%st%d|", ps -> buffer, ps -> reg_avail);
        ps -> reg_avail++;
    }
    return 0;
}
