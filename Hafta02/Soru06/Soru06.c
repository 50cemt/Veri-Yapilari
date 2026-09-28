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
    struct Node* node4 = (struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || node2 == NULL || node3 == NULL || node4 == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    head->data = 10;
    head->next = node2;

    node2->data = 20;
    node2->next = node3;

    node3->data = 30;
    node3->next = node4;

    node4->data = 40;
    node4->next = NULL;

    int toplam = 0;
    struct Node* temp = head;

    while (temp != NULL) {
        toplam += temp->data;
        temp = temp->next;
    }

    printf("Listedeki elemanlarin toplami: %d\n", toplam);

    free(head);
    free(node2);
    free(node3);
    free(node4);

    return 0;
}