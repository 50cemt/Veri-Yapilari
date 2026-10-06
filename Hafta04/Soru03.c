#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;

void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);

void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    if (q->rear == NULL) {
        q->front = newJob;
        q->rear = newJob;
        return;
    }

    q->rear->next = newJob;
    q->rear = newJob;
}

void processNextJob(Queue* q) {
    if (q->front == NULL) {
        printf("Yazdirilacak is yok, kuyruk bos.\n");
        return;
    }

    PrintJob* temp = q->front;
    printf("Yazdiriliyor: %s\n", temp->fileName);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Kuyruk bos.\n");
        return;
    }

    PrintJob* temp = q.front;
    printf("\n--- Yazici Kuyrugu ---\n");
    int count = 1;
    while (temp != NULL) {
        printf("%d. %s\n", count, temp->fileName);
        temp = temp->next;
        count++;
    }
    printf("----------------------\n");
}

int main() {
    Queue q = {NULL, NULL};
    int choice;
    char fileName[50];

    while (1) {
        printf("\n1. Yeni dosya ekle\n2. Yazdir\n3. Kuyrugu goster\n4. Cikis\nSeciminiz: ");
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            continue;
        }
        getchar(); 

        if (choice == 1) {
            printf("Dosya adi: ");
            fgets(fileName, 50, stdin);
            fileName[strcspn(fileName, "\n")] = 0;
            enqueuePrintJob(&q, fileName);
            printf("'%s' kuyruga eklendi.\n", fileName);
        } else if (choice == 2) {
            processNextJob(&q);
        } else if (choice == 3) {
            showQueue(q);
        } else if (choice == 4) {
            printf("Cikis yapiliyor...\n");
            break;
        } else {
            printf("Gecersiz secim!\n");
        }
    }
    return 0;
}