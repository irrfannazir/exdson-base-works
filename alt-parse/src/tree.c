#include <stdio.h>
#include "tree.h"
#include "../data.h"
#include "pdebug.h"

// void displayStartAndSize(struct Node *root) {
//     if (root == NULL) {
//         return;
//     }
    
//     if(root -> left == NULL && root -> right == NULL){
//         for(int i = root -> start ; i < root -> start + root -> size; i++){
//             printf("%s ", get_token(i));
//         }
//         printf("\n");
//     }

//     // Recursively display left and right children
//     displayStartAndSize(root->right);
//     displayStartAndSize(root->left);
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
        // displayStartAndSize(root);
        printf("\n\n");
        if(status){
            printf("Invalid Expression.\n");
            return 1;
        }
        ptr = find_next_expression(root);
        endloop++;
    }
    return 0;
}
