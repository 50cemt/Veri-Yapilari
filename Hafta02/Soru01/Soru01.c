#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};

int main() {
    
    struct Node* yeniNode = (struct Node*)malloc(sizeof(struct Node));

    
    if (yeniNode == NULL) {
        printf("Bellek tahsis edilemedi!\n");
        return 1;
    }

    
    yeniNode->data = 10;
    yeniNode->next = NULL;

    
    printf("Node icerisindeki deger: %d\n", yeniNode->data);
    printf("Node'un gosterdigi sonraki adres (next): %p\n", (void*)yeniNode->next);

    
    free(yeniNode);

    return 0;
}