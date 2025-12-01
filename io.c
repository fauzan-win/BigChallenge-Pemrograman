#include <stdio.h>
#include "io.h"

void saveToBinary(const char *filename, WordData *wd) {
    FILE *f = fopen(filename, "wb");
    if (!f) {
        printf("Gagal menyimpan file binari.\n");
        return;
    }

    fwrite(&wd->count, sizeof(int), 1, f);
    fwrite(wd->words, sizeof(WordFreq), wd->count, f);

    fclose(f);
}

void displayTopN(WordData *wd, int n) {
    if (n > wd->count) n = wd->count;

    printf("\n=== %d Kata Pertama (urut abjad) ===\n", n);
    for (int i = 0; i < n; i++) {
        printf("%-20s : %d\n", wd->words[i].word, wd->words[i].count);
    }
}
