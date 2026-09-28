#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node3 = (struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || node2 == NULL || node3 == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    head->data = 10;
    head->next = node2;

    node2->data = 20;
    node2->next = node3;

    node3->data = 30;
    node3->next = NULL;

    struct Node* yeniNode = (struct Node*)malloc(sizeof(struct Node));
    if (yeniNode == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    yeniNode->data = 40;
    yeniNode->next = NULL;

    struct Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = yeniNode;

    temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    temp = head;
    while (temp != NULL) {
        struct Node* silinecek = temp;
        temp = temp->next;
        free(silinecek);
    }

    return 0;
}