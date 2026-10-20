#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int val) {
    if (root == NULL) {
        return createNode(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    }
    return root;
}

int search(Node* root, int val) {
    if (root == NULL) {
        return 0;
    }
    if (root->data == val) {
        return 1;
    }
    if (val < root->data) {
        return search(root->left, val);
    }
    return search(root->right, val);
}

int findMin(Node* root) {
    Node* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->data;
}

int main() {
    Node* root = NULL;
    int numbers[] = {40, 20, 60, 10, 30, 50, 70};
 
    for (int i = 0; i < 7; i++)
        root = insert(root, numbers[i]);
 
    if (search(root, 30))
        printf("30 agacta bulundu.\n");
    else
        printf("30 agacta bulunamadi.\n");
 
    if (search(root, 90))
        printf("90 agacta bulundu.\n");
    else
        printf("90 agacta bulunamadi.\n");
 
    if (root != NULL)
        printf("En kucuk eleman: %d\n", findMin(root));
 
    return 0;
}