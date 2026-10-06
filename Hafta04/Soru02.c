#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);
void printRecursive(Word* node);

void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    strcpy(newWord->text, text);
    newWord->next = *top;
    *top = newWord;
}

void popWord(Word** top) {
    if (*top == NULL) {
        printf("Geri alinacak islem yok.\n");
        return;
    }
    Word* temp = *top;
    *top = (*top)->next;
    free(temp);
}

void printRecursive(Word* node) {
    if (node == NULL) return;
    printRecursive(node->next);
    printf("%s ", node->text);
}

void showWords(Word* top) {
    if (top == NULL) {
        printf("Metin bos.\n");
        return;
    }
    printRecursive(top);
    printf("\n");
}

int main() {
    Word* top = NULL;
    char command[100];
    char word[50];

    printf("Komutlar: add [kelime], undo, show, exit\n");

    while (1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) break;
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "add ", 4) == 0) {
            strcpy(word, command + 4);
            pushWord(&top, word);
        } else if (strcmp(command, "undo") == 0) {
            popWord(&top);
        } else if (strcmp(command, "show") == 0) {
            showWords(top);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Gecersiz komut!\n");
        }
    }
    return 0;
}