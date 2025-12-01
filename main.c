#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "io.h"

int main() {
    WordData wd;
    initWordData(&wd);

    char filename[200];
    printf("Masukkan nama file input (.txt): ");
    scanf("%s", filename);

    loadAndProcessText(filename, &wd);
    sortWords(&wd);

    int choice;

    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1) Simpan ke file biner\n");
        printf("2) Tampilkan N kata teratas\n");
        printf("3) Keluar\n");
        printf("Pilihan anda: ");
        scanf("%d", &choice);

        if (choice == 1) {
            saveToBinary("output.bin", &wd);
            printf("Disimpan ke output.bin\n");
        }
        else if (choice == 2) {
            int n;
            printf("Masukkan n (1-100): ");
            scanf("%d", &n);
            displayTopN(&wd, n);
        }
        else if (choice == 3) {
            break;
        }
        else {
            printf("Pilihan tidak valid!\n");
        }
    }

    return 0;
}
