#ifndef TREE_H
#define TREE_H
#define MAX 500


// Define the structure for a node in the binary tree
struct Node {
    int data;
    int start;
    int size;
    struct Node* left;
    struct Node* right;
};

extern char *token[MAX];
extern int type[MAX];
void printLeafNodes(struct Node* root);

#endif