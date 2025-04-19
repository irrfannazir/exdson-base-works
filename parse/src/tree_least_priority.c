#include "../include/tree.h"
#include "../include/tree_node.h"
#include "../data.h"
#include <string.h>
#include <stdio.h>



int find_the_least_priority(int start, int size){
    int bracket_is_opened = 0;
    int index = -1;
    int priority = -1;
    int i = start;
    while(i < start + size){
        if(strcmp(token[i], "(") == 0){
            bracket_is_opened = 1;
        }else if(strcmp(token[i], ")") == 0){
            bracket_is_opened = 0;
        }else if(bracket_is_opened == 0){
            if(strcmp(token[i], "/") == 0 && priority < 0){
                index = i;
                priority = 0;
            }else if(strcmp(token[i], "*") == 0 && priority < 1){
                index = i;
                priority = 1;
            }else if(strcmp(token[i], "+") == 0 && priority < 2){
                index = i;
                priority = 2;
            }else if(strcmp(token[i], "-") == 0 && priority < 3){
                index = i;
                priority = 3;
            }else if(strcmp(token[i], "==") == 0 && priority < 4){
                index = i;
                priority = 4;
            }else if(strcmp(token[i], "<=") == 0 && priority < 5){
                index = i;
                priority = 5;
            }else if(strcmp(token[i], ">=") == 0 && priority < 6){
                index = i;
                priority = 6;
            }else if(strcmp(token[i], "!=") == 0 && priority < 7){
                index = i;
                priority = 7;
            }
        }
        i++;
    }
    return index;
}

void display_postfix_reversed(struct Node *root){
    if (root == NULL) return;

    // Create an auxiliary queue for level order traversal
    struct Node* queue[100];  // Assuming a max tree size of 100 for simplicity
    int front = 0, rear = 0;

    // Enqueue root
    printf("\nPostfix exp: ");
    queue[rear++] = root;
    while (front < rear) {
        struct Node* current = queue[front++];

        // Add the current node's value to the array
        // arr[index] = current->data;

        if(current -> size == 1 && current -> right == NULL && current -> left == NULL
        ){
            printf("%s\t", token[current->start]);
        }

        // Enqueue left and right children if they exist
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    printf("\n");
}

void display_postfix(struct Node *root){
    // If the tree is empty, return
    if (root == NULL) {
        return;
    }
    // If the node is a leaf node (both left and right are NULL), print the data
    if (root->left == NULL && root->right == NULL) {
        for(int i = root -> start; i < root -> start + root -> size; i++){
            printf("%s ", token[i]);
        }
        // printf(" ( ::%d:: ) ", root -> data);
    }

    // Recurse for left and right subtrees
    if (root->left != NULL) {
        display_postfix(root->left);
    }
    if (root->right != NULL) {
        display_postfix(root->right);
    }
}
