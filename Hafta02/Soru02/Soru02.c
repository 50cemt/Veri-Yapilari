#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};

int main() {
    
    struct Node* node1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* node2 = (struct Node*)malloc(sizeof(struct Node));

    if (node1 == NULL || node2 == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    
    node1->data = 10;
    node1->next = node2;

    node2->data = 20;
    node2->next = NULL;

    
    printf("1. Node verisi (node1->data)       : %d\n", node1->data);
    printf("2. Node verisi (node1->next->data) : %d\n", node1->next->data);

    printf("\nBagli Liste: %d -> %d -> NULL\n", node1->data, node1->next->data);

    
    free(node1);
    free(node2);

    return 0;
}