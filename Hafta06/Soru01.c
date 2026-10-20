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

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int n, val;

    printf("Kac adet sayi ekleyeceksiniz: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("%d. sayiyi girin: ", i + 1);
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    return 0;
}