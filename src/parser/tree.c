#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/tree.h"
#include "parse/parseState.h"
#include "data.h"
#include "parse/pdebug.h"

#ifdef DISPLAY_TREE
    void displayTree(struct Node *root) {
        if (root == NULL) {
            return;
        }
        
        if(root -> left == NULL && root -> right == NULL){
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

    if(NODE_RIGHT) shrink_the_tree(reg_avail, root->right);
    if(NODE_LEFT) shrink_the_tree(reg_avail, root->left);

    FILE *fh;

    if(
        NODE_LEFT           != NULL &&
        NODE_RIGHT          != NULL &&
        NODE_RIGHT_RIGHT    != NULL &&
        NODE_RIGHT_LEFT     != NULL &&
        NODE_LEFT -> type           == OPERATOR &&
        NODE_RIGHT -> type          == BINARY_EXPRESSION &&
        NODE_RIGHT_RIGHT -> type    == EXPRESSION &&
        NODE_RIGHT_LEFT  -> type    == EXPRESSION
    ){
        fh = fopen(IC_FILENAME, "a");
        fprintf(fh, "t%d = ", *reg_avail);
        printNode(fh, NODE_RIGHT_RIGHT);
        printNode(fh, NODE_LEFT);
        printNode(fh, NODE_RIGHT_LEFT);
        fputs(";\n", fh);
        fclose(fh);
        root -> var = (char *)malloc(VAR_MAX * sizeof(char));
        sprintf(root -> var, "t%d", *reg_avail);
        free(NODE_RIGHT_LEFT);
        free(NODE_RIGHT_RIGHT);
        free(NODE_RIGHT);
        free(NODE_LEFT);
        NODE_RIGHT = NULL;
        NODE_LEFT = NULL;
        (*reg_avail)++;
        
    }
}

/*It is the where parsing tree in implemented*/
int parsing_tree_analysis(struct parseState *ps, char *format, int start, int size){
    struct Node *root = createNode(format, EXPRESSION, start, size);
    struct Node *ptr = find_next_expression(root);
    int endloop = 0;
    while(ptr != NULL && endloop < 20){
        #ifdef P_TREE_MODE
         printf("from %s", get_token(ptr -> start));
         printf("to %s\n", get_token(ptr -> start + ptr -> size));
        #endif
        int status = analyze_expression(ptr);
        #ifdef DISPLAY_TREE
            // displayTree(root); 
            // printf("\n\n");
        #endif
        if(status){
            printf("Invalid Expression.\n");
            return 0;
        }
        ptr = find_next_expression(root);
        endloop++;
    }
    int rg = ps -> reg_avail;
    shrink_the_tree(&rg, root);
    char var[VAR_MAX];
    sprintf(var, "t%d|\0", rg);
    ps -> reg_avail = rg;
    strcat(ps -> buffer, var);
    #ifdef DISPLAY_TREE
        displayTree(root); 
        printf(";\n");
    #endif
    return 0;
}
