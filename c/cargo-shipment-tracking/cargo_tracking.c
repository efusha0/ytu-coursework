#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kargo bilgilerini tutacak yapı (structure)
typedef struct Kargo {
    int gondericiID;
    int takipKodu;
    char ad[51];
    char sehir[51];
    char gun[21];
    char durum[21];
    struct Kargo *next;
} Kargo;

// Şehir bazlı rapor istatistiklerini tutacak yapı
typedef struct SehirRapor {
    char sehirAdi[51];
    int teslimEdildiSayisi;
    int beklemedeSayisi;
    struct SehirRapor *next;
} SehirRapor;

// Fonksiyonlar
Kargo* kargoOkuVeSiraliEkle(Kargo* head, const char* dosyaAdi);
Kargo* siraliEkle(Kargo* head, Kargo* yeniKargo);
void listeyiYazdir(Kargo* head, const char* mesaj);
void gondericiDosyalariOlustur(Kargo* head);
void bekleyenleriYaz(Kargo* head, const char* dosyaAdi);
void raporOlustur(Kargo* head, const char* dosyaAdi);
SehirRapor* sehirRaporListesineEkleVeyaGuncelle(SehirRapor* raporHead, const char* sehir, const char* durum);
void bellegeSerbestBirakKargo(Kargo* head);
void bellegeSerbestBirakSehirRapor(SehirRapor* head);

int main() {
    Kargo* kargoListesi = NULL;

    kargoListesi = kargoOkuVeSiraliEkle(kargoListesi, "kargolar.txt");

    listeyiYazdir(kargoListesi, "Kargo Listesi (Takip Koduna Gore Sirali):");

    gondericiDosyalariOlustur(kargoListesi);
    printf("Gonderici dosyalari olusturuldu.\n");

    bekleyenleriYaz(kargoListesi, "bekleyenler.txt");
    printf("bekleyenler.txt olusturuldu.\n");

    raporOlustur(kargoListesi, "rapor.txt");
    printf("rapor.txt olusturuldu.\n");

    bellegeSerbestBirakKargo(kargoListesi);

    return 0;
}

// kargolar.txt dosyasından verileri okur ve sıralı bağlı listeye ekler
Kargo* kargoOkuVeSiraliEkle(Kargo* head, const char* dosyaAdi) {
    FILE* dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL) {
        perror("HATA: kargolar.txt dosyasi acilamadi");
        return head;
    }

    Kargo tempKargo;
    // Dosya sonuna kadar veya okuma hatası olana kadar satır satır oku
    while (fscanf(dosya, "%d %d %50s %50s %20s %20s",
                  &tempKargo.gondericiID, &tempKargo.takipKodu,
                  tempKargo.ad, tempKargo.sehir, tempKargo.gun, tempKargo.durum) == 6) {

        Kargo* yeniKargo = (Kargo*)malloc(sizeof(Kargo));
        if (yeniKargo == NULL) {
            perror("HATA: Kargo dugumu icin bellek ayrilamadi");
            fclose(dosya); // Dosyayı kapat
            return head;
        }
        // Okunan verileri yeni düğüme kopyala
        yeniKargo->gondericiID = tempKargo.gondericiID;
        yeniKargo->takipKodu = tempKargo.takipKodu;
        strcpy(yeniKargo->ad, tempKargo.ad);
        strcpy(yeniKargo->sehir, tempKargo.sehir);
        strcpy(yeniKargo->gun, tempKargo.gun);
        strcpy(yeniKargo->durum, tempKargo.durum);
        yeniKargo->next = NULL;

        head = siraliEkle(head, yeniKargo); // Yeni kargoyu listeye sıralı ekle
    }

    fclose(dosya);
    return head;
}

// Yeni kargo düğümünü takip koduna göre sıralı olarak listeye ekler
Kargo* siraliEkle(Kargo* head, Kargo* yeniKargo) {
    if (head == NULL || yeniKargo->takipKodu < head->takipKodu) {
        yeniKargo->next = head;
        return yeniKargo;
    }

    Kargo* current = head;
    while (current->next != NULL && current->next->takipKodu < yeniKargo->takipKodu) {
        current = current->next;
    }
    yeniKargo->next = current->next;
    current->next = yeniKargo;
    return head;
}

// Bağlı listedeki tüm kargoları belirtilen mesajla birlikte ekrana yazdır
void listeyiYazdir(Kargo* head, const char* mesaj) {
    printf("\n%s\n", mesaj);
    Kargo* current = head;
    if (current == NULL) {
        printf("Liste bos.\n");
        return;
    }
    while (current != NULL) {
        printf("%d %d %s %s %s %s\n",
               current->gondericiID, current->takipKodu,
               current->ad, current->sehir, current->gun, current->durum);
        current = current->next;
    }
    printf("\n");
}

// Her gönderici için [Ad].txt formatında dosyalar oluştur
void gondericiDosyalariOlustur(Kargo* head) {
    Kargo* current = head;
    char dosyaAdi[60];

    while (current != NULL) {
        sprintf(dosyaAdi, "%s.txt", current->ad);
        FILE* gondericiDosyasi = fopen(dosyaAdi, "a");
        if (gondericiDosyasi == NULL) {
            perror("HATA: Gonderici dosyasi olusturulamadi/acilamadi");
        } else {
            fprintf(gondericiDosyasi, "%s adli gondericiye ait %d no'lu kargo,\n",
                    current->ad, current->gondericiID);
            fprintf(gondericiDosyasi, "%s gunu %s sehrine gonderildi.\n",
                    current->gun, current->sehir);
            fprintf(gondericiDosyasi, "Durum: %s.\n\n", current->durum);
            fclose(gondericiDosyasi);
        }
        current = current->next;
    }
}

void bekleyenleriYaz(Kargo* head, const char* dosyaAdi) {
    FILE* dosya = fopen(dosyaAdi, "w");
    if (dosya == NULL) {
        perror("HATA: bekleyenler.txt acilamadi/olusturulamadi");
        return;
    }

    Kargo* current = head;
    while (current != NULL) {
        if (strcmp(current->durum, "Beklemede") == 0) {
            fprintf(dosya, "%d %d %s %s %s %s\n",
                    current->gondericiID, current->takipKodu,
                    current->ad, current->sehir, current->gun, current->durum);
        }
        current = current->next;
    }
    fclose(dosya);
}

// Şehir rapor listesi
SehirRapor* sehirRaporListesineEkleVeyaGuncelle(SehirRapor* raporHead, const char* sehir, const char* durum) {
    SehirRapor* current = raporHead;
    SehirRapor* last = NULL;

    while (current != NULL) {
        if (strcmp(current->sehirAdi, sehir) == 0) {
            if (strcmp(durum, "TeslimEdildi") == 0) {
                current->teslimEdildiSayisi++;
            } else if (strcmp(durum, "Beklemede") == 0) {
                current->beklemedeSayisi++;
            }
            return raporHead;
        }
        last = current;
        current = current->next;
    }

    SehirRapor* yeniSehir = (SehirRapor*)malloc(sizeof(SehirRapor));
    if (yeniSehir == NULL) {
        perror("HATA: SehirRapor dugumu icin bellek ayrilamadi");
        return raporHead;
    }
    strcpy(yeniSehir->sehirAdi, sehir);
    yeniSehir->teslimEdildiSayisi = 0;
    yeniSehir->beklemedeSayisi = 0;
    yeniSehir->next = NULL;

    if (strcmp(durum, "TeslimEdildi") == 0) {
        yeniSehir->teslimEdildiSayisi = 1;
    } else if (strcmp(durum, "Beklemede") == 0) {
        yeniSehir->beklemedeSayisi = 1;
    }

    if (last == NULL) {
        raporHead = yeniSehir;
    } else {
        last->next = yeniSehir;
    }
    return raporHead;
}

// Şehir bazlı teslimat raporunu oluşturur ve dosyaya yazar
void raporOlustur(Kargo* head, const char* dosyaAdi) {
    SehirRapor* raporListesi = NULL;
    Kargo* currentKargo = head;

    while (currentKargo != NULL) {
        raporListesi = sehirRaporListesineEkleVeyaGuncelle(raporListesi, currentKargo->sehir, currentKargo->durum);
        currentKargo = currentKargo->next;
    }

    FILE* dosya = fopen(dosyaAdi, "w");
    if (dosya == NULL) {
        perror("HATA: rapor.txt acilamadi/olusturulamadi");
        bellegeSerbestBirakSehirRapor(raporListesi);
        return;
    }

    SehirRapor* currentRapor = raporListesi;
    while (currentRapor != NULL) {
        fprintf(dosya, "%s TeslimEdildi: %d, Beklemede: %d\n",
                currentRapor->sehirAdi,
                currentRapor->teslimEdildiSayisi,
                currentRapor->beklemedeSayisi);
        currentRapor = currentRapor->next;
    }

    fclose(dosya);
    bellegeSerbestBirakSehirRapor(raporListesi);
}

void bellegeSerbestBirakSehirRapor(SehirRapor* head) {
    SehirRapor* current = head;
    SehirRapor* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

void bellegeSerbestBirakKargo(Kargo* head) {
    Kargo* current = head;
    Kargo* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}
