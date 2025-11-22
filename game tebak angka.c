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
