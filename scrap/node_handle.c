#define NULL 0

struct Node{
    int data;
    struct Node *left;
    struct Node *right;
};



void deleteNode(struct Node *newNode){
    if(newNode -> left != NULL){
        deleteNode(newNode -> left);
        newNode -> left = NULL;
    }
    if(newNode -> right != NULL){
        deleteNode(newNode -> right);
        newNode -> right = NULL;
    }
    free(newNode);
    if(newNode -> right == NULL && newNode -> left == NULL){
        return;
    }
}