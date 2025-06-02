#ifndef NODE_H
#define NODE_H

struct Node{
    int data; // Assign the macro value to this variable
    int start;
    int size;
    struct Node *left;
    struct Node *right;
};

void display_postfix_reversed(struct Node *ptr);
void display_postfix(struct Node *ptr);

#endif