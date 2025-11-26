#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USER 20

struct user {
    char nama[20], pass[20];
    int skor;
};

struct user dataUser[MAX_USER];
int jumlahUser = 0;

void clearInput() {
    while (getchar() != '\n');
}

void loadUser() {
    FILE *f = fopen("data pemain.txt", "r");
    if (f == NULL) return;

    while (fscanf(f, "%s %s %d",
        dataUser[jumlahUser].nama,
        dataUser[jumlahUser].pass,
        &dataUser[jumlahUser].skor) == 3)
    {
        jumlahUser++;
        if (jumlahUser >= MAX_USER) break;
    }
    fclose(f);
}

void saveUser() {
    FILE *f = fopen("data pemain.txt", "w");
    if (f == NULL) return;

    for (int i = 0; i < jumlahUser; i++) {
        fprintf(f, "%s %s %d\n",
            dataUser[i].nama,
            dataUser[i].pass,
            dataUser[i].skor);
    }

    fclose(f);
}

int cariUser(char u[]) {
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(dataUser[i].nama, u) == 0) {
            return i;
        }
    }
    return -1;
}

void daftarAkun() {
    char u[30], p[30];

    printf("\n=== DAFTAR ===\n");
    printf("Nama: ");
    scanf("%s", u);
    clearInput();

    if (cariUser(u) != -1) {
        printf("Nama sudah dipakai.\n");
        return;
    }

    printf("Password: ");
    scanf("%s", p);
    clearInput();

    strcpy(dataUser[jumlahUser].nama, u);
    strcpy(dataUser[jumlahUser].pass, p);
    dataUser[jumlahUser].skor = 0;

    jumlahUser++;
    saveUser();

    printf("Registrasi berhasil.\n");
}

int login() {
    char u[30], p[30];

    printf("\n=== LOGIN ===\n");
    printf("Nama: ");
    scanf("%s", u);
    clearInput();
    printf("Password: ");
    scanf("%s", p);
    clearInput();

    int idx = cariUser(u);
    if (idx == -1) {
        printf("Nama tidak ditemukan.\n");
        return -1;
    }

    if (strcmp(dataUser[idx].pass, p) != 0) {
        printf("Password salah.\n");
        return -1;
    }
    printf("Login sukses.\n");
    return idx;
}

void mainGameSingle(int idx) {
    int ronde, rahasia, tebak, batas;
    int totalSkor = 0;

    printf("\n=== MODE SINGLE PLAYER ===\n");
    printf("Batas angka (Default 10): ");
    scanf("%d", &batas);
    clearInput();
    if (batas < 5) batas = 10; 

    printf("Berapa ronde (Default 3)? ");
    scanf("%d", &ronde);
    clearInput();
    if (ronde < 1) ronde = 1;

    for (int r = 1; r <= ronde; r++) {
        printf("\n===== RONDE %d =====\n", r);
        rahasia = (rand() % batas) + 1;
        if (rahasia % 2 == 0)
            printf("CLUE: Angka rahasia GENAP\n");
        else
            printf("CLUE: Angka rahasia GANJIL\n");

        int benar = 0;

        for (int percobaan = 1; percobaan <= 3; percobaan++) {
            printf("Tebakan ke-%d: ", percobaan);
            scanf("%d", &tebak);
            clearInput();

            if (tebak == rahasia) {
                printf("BENAR! Angkanya adalah %d\n", rahasia);
                totalSkor += 10;
                benar = 1;
                break;
            } else {
                printf("SALAH!\n");
            }
        }
        if (!benar) {
            printf("Jawaban benar: %d\n", rahasia);
        }
    }

    dataUser[idx].skor += totalSkor;
    saveUser();

    printf("\n=== PERMAINAN SELESAI ===\n");
    printf("Skor total yang kamu dapat: %d\n", totalSkor);
    printf("Total skor telah disimpan. Lihat di menu 'Lihat Skor'.\n");
}
void modeTurnamen() {
    int batas = 20;
    int rondeTotal = 5;
    int totalP1 = 0, totalP2 = 0;

    printf("\n\t=== MODE TURNAMEN ===\t\n");
    printf("Turnamen ini terdiri dari %d ronde\n", rondeTotal);
    printf("Setiap pemain hanya memiliki 1 kali kesempatan untuk untuk menebak angka setiap ronde\n");
    printf("Silahkan tebak angka dari 1 - 20!\n ");

    for (int r = 1; r <= rondeTotal; r++) {

       printf("\n====================================\n");
       printf("         \tRONDE %d\n", r);
       printf("=====================================\n");

       int rahasia = (rand() % batas) + 1;

       if (rahasia % 2 == 0)
           printf("CLUE: Angka rahasia GENAP\n");
       else
           printf("CLUE: Angka rahasia GANJIL\n");

       int tebak1, tebak2;
       int sKorRondeP1 = 0, sKorRondeP2 = 0;

       printf("\n--- Pemain 1 ---\n");
       printf("Tebakan Anda: ");
       scanf("%d", &tebak1);
       printf("\n--- Pemain 2 ---\n");
       printf("Tebakan Anda: ");
       scanf("%d", &tebak2);

       if (tebak1 == rahasia && tebak2 == rahasia) {
           sKorRondeP1 = 5;
           sKorRondeP2 = 5;
           printf("\nKEDUA PEMAIN BENAR! (+5 poin masing-masing)\n");
       }
       else if (tebak1 == rahasia) {
           sKorRondeP1 = 10;
           printf("\nPemain 1 BENAR! (+10 poin) \n");
       }
       else if (tebak2 == rahasia) {
           sKorRondeP2 = 10;
           printf("\nPemain 2 BENAR! (+10 poin) \n"); 
       }
       else {
           printf("\nTidak ada yang benar.\n");
       }

       printf("Jawaban benar: %d\n", rahasia);

       totalP1 += sKorRondeP1;
       totalP2 += sKorRondeP2;
    }


    printf("\n=== HASIL AKHIR TURNAMEN ===\n");
    printf("TOTAL SKOR Pemain 1: %d\n", totalP1);
    printf("TOTAL SKOR Pemain 2: %d\n", totalP2);

    if (totalP1 > totalP2)
        printf("\nPEMENANG: PEMAIN 1 \n");
    else if (totalP2 > totalP1)
        printf("\nPEMENANG: PEMAIN 2\n");
    else
        printf("\nHASIL SERI! \n");
}
void tampilSkor() {
    printf("\n=== SKOR USER (MODE SINGLE) ===\n");
    for (int i = 0; i < jumlahUser; i++) {
        printf("%d. %s - %d\n", i+1, dataUser[i].nama, dataUser[i].skor);
    }
}

int main() {
    srand(time(NULL));
    loadUser();

    int pilih;
    int loginIndex = -1;

    while (1) {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Daftar\n");
        printf("2. Login\n");
        printf("3. Mode Single\n");
        printf("4. Lihat Skor\n");
        printf("5. Mode Turnamen\n");
        printf("6. Keluar\n");
        printf("Pilih: ");

        if (scanf("%d", &pilih) != 1) {
            clearInput();
            continue;
        }
        clearInput();

        if (pilih == 1) daftarAkun();
        else if (pilih == 2) loginIndex = login();
        else if (pilih == 3) {
            if (loginIndex == -1) {
                printf("Anda harus login terlebih dahulu!\n");
            } else {
                mainGameSingle(loginIndex);
            }
        }
        else if (pilih == 4) tampilSkor();
        else if (pilih == 5) modeTurnamen();
        else if (pilih == 6) {
            printf("\n===Terimakasih telah bermain;)!!===\n");
            break;
        }
        else printf("Pilihan tidak ada.\n");
    }
    return 0;
}

