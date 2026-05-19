#include <stdio.h>
#include "parse/tree.h"
#include "data.h"
#include "parse/pdebug.h"

#ifdef DISPLAY_TREE
    // void displayTree(struct Node *root) {
    //     if (root == NULL) {
    //         return;
    //     }
        
    //     if(root -> left == NULL && root -> right == NULL){
    //         for(int i = root -> start ; i < root -> start + root -> size; i++){
    //             printf("%s ", get_token(i));
    //         }
    //         printf("\n");
    //     }
    //     displayTree(root->right);
    //     displayTree(root->left);
    // }
#endif

// void printNode(struct Node *ptr){
//     for(int i = ptr -> start ; i < ptr -> start + ptr -> size; i++){
//         printf("%s ", get_token(i));
//     }
// }

// static inline void draw_the_tree(struct Node *root){
//     if (root == NULL) {
//         return;
//     }

//     #define NODE_LEFT           root -> left
//     #define NODE_RIGHT          root -> right
//     #define NODE_RIGHT_RIGHT    root -> right -> right
//     #define NODE_RIGHT_LEFT     root -> right -> left

//     if(NODE_RIGHT) draw_the_tree(root->right);
//     if(NODE_LEFT) draw_the_tree(root->left);

//     if(
//         NODE_LEFT           != NULL &&
//         NODE_RIGHT          != NULL &&
//         NODE_RIGHT_RIGHT    != NULL &&
//         NODE_RIGHT_LEFT     != NULL &&
//         NODE_LEFT -> type           == OPERATOR &&
//         NODE_RIGHT -> type          == BINARY_EXPRESSION &&
//         NODE_RIGHT_RIGHT -> type    == EXPRESSION &&
//         NODE_RIGHT_LEFT  -> type    == EXPRESSION
//     ){
//         printf("t1 = ");
//         printNode(NODE_RIGHT_RIGHT);
//         printNode(NODE_LEFT);
//         printNode(NODE_RIGHT_LEFT);
//         puts("\n");

//     }
// }

/*It is the where parsing tree in implemented*/
int parsing_tree_analysis(char *format, int start, int size){
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
            return 1;
        }
        ptr = find_next_expression(root);
        endloop++;
    }
    // draw_the_tree(root);
    return 0;
}
