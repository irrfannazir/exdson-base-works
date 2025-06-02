#include "../data.h"
#include "node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int is_variable_declared(int index){
    for(int i = 0; i < line_size; i++){
        int variable_index = parametre_list[i][1];
        if(
            line_method[i] == 0
                &&
            strcmp(token[variable_index], token[index]) == 0
        ){
            return 1;
        }
    }
    return 0;
}

int is_unidentified(struct Node *ptr){
    if(ptr -> size > 1){
        return 1;
    }
    else if(ptr -> size == 1){
        if(type[ptr -> start] == TOKEN_INTEGER){
            return 0;
        }else if(type[ptr -> start] == TOKEN_IDENTIFIER && is_variable_declared(ptr -> start)){
            return 0;
        }
        return 1;
    }
}

struct Node *find_next_expression(struct Node* root) {
    int arr[500];
    int index = 0;
    if (root == NULL) return NULL;
    if (root -> data == 0 && root -> size > 1 && root -> right == NULL && root -> left == NULL) return root;

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
            current -> data == 0
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

void *createNode(int value, int start, int size){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->start = start;
    newNode->size = size;
    newNode->left = 0;
    newNode->right = 0;
    return newNode;
}

void save_expression_root(struct Node *root){
    return;
}
