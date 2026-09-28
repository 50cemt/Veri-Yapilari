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

    int silinecekDeger;
    printf("Silmek istediginiz degeri giriniz: ");
    scanf("%d", &silinecekDeger);

    struct Node* temp = head;
    struct Node* onceki = NULL;

    if (temp != NULL && temp->data == silinecekDeger) {
        head = temp->next;
        free(temp);
    } else {
        while (temp != NULL && temp->data != silinecekDeger) {
            onceki = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("%d degeri listede bulunamadi.\n", silinecekDeger);
        } else {
            onceki->next = temp->next;
            free(temp);
        }
    }

    temp = head;
    printf("Guncel Liste: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    temp = head;
    while (temp != NULL) {
        struct Node* sil = temp;
        temp = temp->next;
        free(sil);
    }

    return 0;
}