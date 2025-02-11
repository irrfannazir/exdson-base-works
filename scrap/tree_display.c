#include <stdio.h>
#include <stdlib.h>
#include "tree.h"






// extern int type[MAX];
// extern char *token[MAX];

// Function to create a new node with a given value
// struct Node* createNode(int data) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->left = newNode->right = NULL;
//     return newNode;
// }

// Function to print leaf nodes of the binary tree
void printLeafNodes(struct Node* root) {
    // If the tree is empty, return
    if (root == NULL) {
        return;
    }

    // If the node is a leaf node (both left and right are NULL), print the data
    if (root->left == NULL && root->right == NULL) {
        // printf("token index: %d \n", root -> start);
        printf("token: %s \n", token[root -> start]);

    }

    // Recurse for left and right subtrees
    if (root->left != NULL) {
        printLeafNodes(root->left);
    }
    if (root->right != NULL) {
        printLeafNodes(root->right);
    }
    // printf("\n");
}

/*

// Main function to test the leaf node display
int main() {
    // Create a binary tree
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    root->left->left->left = createNode(8);
    
    printf("Leaf nodes of the tree: ");
    printLeafNodes(root); // Call the function to display leaf nodes
    printf("\n");

    return 0;
}


*/
