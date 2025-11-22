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
