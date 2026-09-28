#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};

int main() {
    
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    struct Node* ikinci = (struct Node*)malloc(sizeof(struct Node));
    struct Node* ucuncu = (struct Node*)malloc(sizeof(struct Node));

    if (head == NULL || ikinci == NULL || ucuncu == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    
    head->data = 10;
    head->next = ikinci;

    ikinci->data = 20;
    ikinci->next = ucuncu;

    ucuncu->data = 30;
    ucuncu->next = NULL;


    struct Node* temp = head;

    printf("Bagli Liste Elemanlari:\n");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");

    
    free(head);
    free(ikinci);
    free(ucuncu);

    return 0;
}