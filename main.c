#include <stdio.h>
#include <string.h>
#include "textutil.h"
#include "datastore.h"

int main() {
    char inputFile[100];
    char binFile[] = "output.bin";

    LetterGroup groups[26];
    init_groups(groups);

    printf("Masukkan nama file input (txt): ");
    scanf("%s", inputFile);

    FILE *fp = fopen(inputFile, "r");
    if (!fp) {
        printf("Tidak dapat membuka file!\n");
        return 0;
    }

    char line[1000];
    int isTitle = 0, isBody = 0, skipURL = 0;

    // PARSING
    while (fgets(line, sizeof(line), fp)) {
        process_line(line, &isTitle, &isBody, &skipURL);

        if (!isTitle && !isBody) continue;

        char *token = strtok(line, " ");
        while (token) {
            add_word(groups, token);
            token = strtok(NULL, " ");
        }
    }
    fclose(fp);

    sort_groups(groups);

    int choice;
    do {
        printf("\n1) Simpan ke file biner\n");
        printf("2) Tampilkan top-n\n");
        printf("3) Keluar\n");
        printf("Pilihan anda: ");
        scanf("%d", &choice);

        if (choice == 1) {
            save_binary(binFile, groups);
            printf("Data telah disimpan ke '%s'\n", binFile);
        }

        else if (choice == 2) {
            int n;
            printf("Masukkan n (1–25): ");
            scanf("%d", &n);

            LetterGroup temp[26];
            load_binary(binFile, temp);

            display_top_n(temp, n);
        }

    } while (choice != 3);

    return 0;
}
