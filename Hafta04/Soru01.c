#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

void addSongToEnd(Song** head, char* name);
void removeSong(Song** head, char* name);
void playNext(Song** current);
void playPrevious(Song** current);
void displayPlaylist(Song* head);

void addSongToEnd(Song** head, char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;
}

void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos!\n");
        return;
    }

    Song* temp = *head;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Sarki bulunamadi!\n");
        return;
    }

    if (temp == *head) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }

    free(temp);
    printf("%s listeden silindi.\n", name);
}

void playNext(Song** current) {
    if (*current == NULL) {
        printf("Su an calan sarki yok veya liste bos.\n");
        return;
    }
    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Su an caliyor: %s\n", (*current)->name);
    } else {
        printf("Listenin sonundasiniz, sonraki sarki yok.\n");
    }
}

void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Su an calan sarki yok veya liste bos.\n");
        return;
    }
    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Su an caliyor: %s\n", (*current)->name);
    } else {
        printf("Listenin basindasiniz, onceki sarki yok.\n");
    }
}

void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("Liste bos!\n");
        return;
    }
    Song* temp = head;
    printf("\n--- Calma Listesi ---\n");
    while (temp != NULL) {
        printf("- %s\n", temp->name);
        temp = temp->next;
    }
    printf("---------------------\n");
}

int main() {
    Song* head = NULL;
    Song* current = NULL;
    int choice;
    char name[50];

    while (1) {
        printf("\n1. Sarki Ekle\n2. Sarki Sil\n3. Sonraki Sarki\n4. Onceki Sarki\n5. Listeyi Goster\n6. Cikis\nSeciminiz: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            printf("Sarki adi: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            addSongToEnd(&head, name);
            if (current == NULL) {
                current = head;
            }
            printf("'%s' eklendi.\n", name);
        } else if (choice == 2) {
            printf("Silinecek sarki adi: ");
            fgets(name, 50, stdin);
            name[strcspn(name, "\n")] = 0;
            
            if (current != NULL && strcmp(current->name, name) == 0) {
                if (current->next != NULL) {
                    current = current->next;
                } else if (current->prev != NULL) {
                    current = current->prev;
                } else {
                    current = NULL;
                }
            }
            removeSong(&head, name);
        } else if (choice == 3) {
            playNext(&current);
        } else if (choice == 4) {
            playPrevious(&current);
        } else if (choice == 5) {
            displayPlaylist(head);
            if (current != NULL) {
                printf("Su an calan: %s\n", current->name);
            }
        } else if (choice == 6) {
            printf("Cikis yapiliyor...\n");
            break;
        } else {
            printf("Gecersiz secim!\n");
        }
    }
    return 0;
}