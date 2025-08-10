#include "node.h"
#include "parseh.h"
#include "../data.h"
#include <stdio.h>
#include <stdlib.h>

int is_declared_variable(int index){
    return 0;
}

int is_unidentified(struct Node *ptr){
    if(ptr -> size > 1){
        return 1;
    }
    else if(ptr -> size == 1){
        if(get_type(ptr -> start) == TOKEN_INTEGER){
            return 0;
        }else if(get_type(ptr -> start) == TOKEN_IDENTIFIER && is_declared_variable(ptr -> start)){
            return 0;
        }
        return 1;
    }
    return ptr -> size != 1;
}

struct Node *find_next_expression(struct Node* root) {
    int index = 0;
    if (root == NULL) return NULL;
    if (root -> data == 0 && root -> size > 1 && root -> right == NULL && root -> left == NULL) return root;
    int arr[500];

    // Create an auxiliary queue for level order traversal
    struct Node* queue[100];  // Assuming a max tree size of 100 for simplicity
    int front = 0, rear = 0;

    // Enqueue root
    queue[rear++] = root;
    while (front < rear) {
        struct Node* current = queue[front++];

        // Add the current node's value to the array
        arr[index] = current->data;

        if(
            current -> data == EXPRESSION
                &&
            is_unidentified(current)
                &&
            current -> right == NULL
                &&
            current -> left == NULL
        ){
            return current;
        }
        (index)++;

        // Enqueue left and right children if they exist
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    return NULL;
}