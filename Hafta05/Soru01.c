#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Hasta {
    int id;
    char isim[100];
    char durum[20];
    struct Hasta *next;
} Hasta;

typedef struct {
    Hasta *front;
    Hasta *rear;
} Kuyruk;

typedef struct {
    Hasta *top;
} Yigin;

typedef struct {
    Hasta *head;
    Hasta *tail;
} BagliListe;

void kuyrukBaslat(Kuyruk *k) {
    k->front = NULL;
    k->rear = NULL;
}

void yiginBaslat(Yigin *y) {
    y->top = NULL;
}

void listeBaslat(BagliListe *bl) {
    bl->head = NULL;
    bl->tail = NULL;
}

void enqueue(Kuyruk *k, int id, const char *isim) {
    Hasta *yeniHasta = (Hasta *)malloc(sizeof(Hasta));
    if (yeniHasta == NULL) {
        printf("Hata: Bellek tahsis edilemedi!\n");
        return;
    }

    yeniHasta->id = id;
    strncpy(yeniHasta->isim, isim, sizeof(yeniHasta->isim) - 1);
    yeniHasta->isim[sizeof(yeniHasta->isim) - 1] = '\0';
    strcpy(yeniHasta->durum, "bekliyor");
    yeniHasta->next = NULL;

    if (k->rear == NULL) {
        k->front = yeniHasta;
        k->rear = yeniHasta;
    } else {
        k->rear->next = yeniHasta;
        k->rear = yeniHasta;
    }

    printf("[KAYIT] Hasta ID: %d, Isim: %s bekleme kuyruguna eklendi.\n", yeniHasta->id, yeniHasta->isim);
}

Hasta* dequeue(Kuyruk *k) {
    if (k->front == NULL) {
        printf("[UYARI] Bekleme kuyrugu bos! Muayeneye alinacak hasta yok.\n");
        return NULL;
    }

    Hasta *cikarilan = k->front;
    k->front = k->front->next;

    if (k->front == NULL) {
        k->rear = NULL;
    }

    cikarilan->next = NULL;
    return cikarilan;
}


void push(Yigin *y, Hasta *hasta) {
    if (hasta == NULL) return;

    strcpy(hasta->durum, "muayenede");
    hasta->next = y->top;
    y->top = hasta;

    printf("[MUAYENE] Hasta ID: %d, Isim: %s muayene odasina alindi.\n", hasta->id, hasta->isim);
}

Hasta* pop(Yigin *y) {
    if (y->top == NULL) {
        printf("[UYARI] Muayene odasi (yigin) bos! Tamamlanacak hasta yok.\n");
        return NULL;
    }

    Hasta *cikarilan = y->top;
    y->top = y->top->next;
    cikarilan->next = NULL;

    return cikarilan;
}


void gecmiseEkle(BagliListe *bl, Hasta *hasta) {
    if (hasta == NULL) return;

    strcpy(hasta->durum, "tamamlandi");
    hasta->next = NULL;

    if (bl->head == NULL) {
        bl->head = hasta;
        bl->tail = hasta;
    } else {
        bl->tail->next = hasta;
        bl->tail = hasta;
    }

    printf("[TAMAMLANDI] Hasta ID: %d, Isim: %s muayenesi tamamlandi ve gecmise eklendi.\n", hasta->id, hasta->isim);
}


void bekleyenleriListele(Kuyruk *k) {
    printf("--- Bekleyen Hastalar ---\n");
    if (k->front == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta *gecici = k->front;
    while (gecici != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", gecici->id, gecici->isim, gecici->durum);
        gecici = gecici->next;
    }
}

void muayenedekileriListele(Yigin *y) {
    printf("--- Muayene Odasindaki Hastalar ---\n");
    if (y->top == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta *gecici = y->top;
    while (gecici != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", gecici->id, gecici->isim, gecici->durum);
        gecici = gecici->next;
    }
}

void tamamlananlariListele(BagliListe *bl) {
    printf("--- Tamamlanan Hastalar ---\n");
    if (bl->head == NULL) {
        printf("Hasta yok.\n");
        return;
    }
    Hasta *gecici = bl->head;
    while (gecici != NULL) {
        printf("Hasta ID: %d, Isim: %s, Durum: %s\n", gecici->id, gecici->isim, gecici->durum);
        gecici = gecici->next;
    }
}

void tumDurumuListele(Kuyruk *k, Yigin *y, BagliListe *bl) {
    printf("\n=== Tum Islemler Sonrasi ===\n");
    bekleyenleriListele(k);
    muayenedekileriListele(y);
    tamamlananlariListele(bl);
}


void listeBelleginiTemizle(Hasta *baslangic) {
    Hasta *gecici;
    while (baslangic != NULL) {
        gecici = baslangic;
        baslangic = baslangic->next;
        free(gecici);
    }
}

void tumBellegiTemizle(Kuyruk *k, Yigin *y, BagliListe *bl) {
    listeBelleginiTemizle(k->front);
    listeBelleginiTemizle(y->top);
    listeBelleginiTemizle(bl->head);
    k->front = k->rear = NULL;
    y->top = NULL;
    bl->head = bl->tail = NULL;
}

// --- ANA PROGRAM ---

int main() {
    Kuyruk beklemeKuyrugu;
    Yigin muayeneYigini;
    BagliListe gecmisListesi;

    kuyrukBaslat(&beklemeKuyrugu);
    yiginBaslat(&muayeneYigini);
    listeBaslat(&gecmisListesi);

    int secim;
    int otomatikId = 1;
    char isimGirdisi[100];

    while (1) {
        printf("\n========================================\n");
        printf("     HASTANE HASTA TAKIP SISTEMI\n");
        printf("========================================\n");
        printf("1. Yeni Hasta Ekle (Kuyruga - enqueue)\n");
        printf("2. Siradaki Hastayi Muayeneye Al (dequeue -> push)\n");
        printf("3. Muayeneyi Tamamla (pop -> gecmiseEkle)\n");
        printf("4. Bekleyen Hastalari Listele (Kuyruk)\n");
        printf("5. Muayene Odasindaki Hastalari Listele (Yigin)\n");
        printf("6. Tamamlanan Hastalari Listele (Bagli Liste)\n");
        printf("7. Tum Durumu Listele\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");

        if (scanf("%d", &secim) != 1) {
            printf("[HATA] Gecersiz giris! Lutfen bir sayi giriniz.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (secim) {
            case 1:
                printf("Hasta Adini Giriniz: ");
                scanf(" %[^\n]", isimGirdisi); 
                enqueue(&beklemeKuyrugu, otomatikId++, isimGirdisi);
                break;

            case 2: {
                Hasta *muayeneyeAlinan = dequeue(&beklemeKuyrugu);
                if (muayeneyeAlinan != NULL) {
                    push(&muayeneYigini, muayeneyeAlinan);
                }
                break;
            }

            case 3: {
                Hasta *tamamlananHasta = pop(&muayeneYigini);
                if (tamamlananHasta != NULL) {
                    gecmiseEkle(&gecmisListesi, tamamlananHasta);
                }
                break;
            }

            case 4:
                printf("\n");
                bekleyenleriListele(&beklemeKuyrugu);
                break;

            case 5:
                printf("\n");
                muayenedekileriListele(&muayeneYigini);
                break;

            case 6:
                printf("\n");
                tamamlananlariListele(&gecmisListesi);
                break;

            case 7:
                tumDurumuListele(&beklemeKuyrugu, &muayeneYigini, &gecmisListesi);
                break;

            case 0:
                tumBellegiTemizle(&beklemeKuyrugu, &muayeneYigini, &gecmisListesi);
                printf("Bellek temizlendi. Programdan cikiliyor...\n");
                return 0;

            default:
                printf("[UYARI] Gecersiz secim! Lutfen 0-7 arasinda bir deger giriniz.\n");
        }
    }

    return 0;
}