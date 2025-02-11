#include "../include/tree.h"
#include "../include/tree_node.h"
#include "../data.h"
#include <stdlib.h>

#include <stdio.h>

struct Node *find_the_exp(struct Node* root) {
    int arr[MAX];
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

        if(current -> data == 0 && current -> size > 1 && current -> right == NULL && current -> left == NULL
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
    // printf("Finished the program.\n");
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

void add_the_root(struct Node *root){
    return;
}
