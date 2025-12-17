#include <stdio.h>
#include <string.h>
#include "word.h"

void sort_words(LetterGroup *g) {
    for (int i = 0; i < g->count - 1; i++) {
        for (int j = i + 1; j < g->count; j++) {
            Word *a = &g->words[i];
            Word *b = &g->words[j];
            if (a->freq < b->freq ||
               (a->freq == b->freq && a->length < b->length) ||
               (a->freq == b->freq && a->length == b->length && strcmp(a->word, b->word) < 0)) {
                Word tmp = *a;
                *a = *b;
                *b = tmp;
            }
        }
    }
}

void save_binary(const char *fname) {
    FILE *fp = fopen(fname, "wb");
    if (!fp) {
        printf("Gagal membuat file binari!\n");
        return;
    }

    for (int i = 0; i < 26; i++) {
        fwrite(&groups[i].letter, sizeof(char), 1, fp);
        fwrite(&groups[i].count, sizeof(int), 1, fp);
        for (int j = 0; j < groups[i].count; j++) {
            fwrite(&groups[i].words[j].length, sizeof(int), 1, fp);
            fwrite(groups[i].words[j].word, sizeof(char), groups[i].words[j].length, fp);
            fwrite(&groups[i].words[j].freq, sizeof(int), 1, fp);
        }
    }
    fclose(fp);
    binary_saved = 1;
}

void display_from_binary(const char *fname, int n) {
    FILE *fp = fopen(fname, "rb");
    if (!fp) {
        printf("File binari tidak ditemukan!\n");
        return;
    }

    for (int i = 0; i < 26; i++) {
        char letter;
        int count;
        fread(&letter, sizeof(char), 1, fp);
        fread(&count, sizeof(int), 1, fp);

        printf("%c {", letter);
        for (int j = 0; j < count && j < n; j++) {
            int len, freq;
            char word[MAX_WORD] = {0};
            fread(&len, sizeof(int), 1, fp);
            fread(word, sizeof(char), len, fp);
            word[len] = '\0';
            fread(&freq, sizeof(int), 1, fp);
            printf("%s (%d)", word, freq);
            if (j < count - 1 && j < n - 1) printf(", ");
        }
        printf("}\n");

        for (int j = n; j < count; j++) {
            int len, freq;
            char dummy[MAX_WORD];
            fread(&len, sizeof(int), 1, fp);
            fread(dummy, sizeof(char), len, fp);
            fread(&freq, sizeof(int), 1, fp);
        }
    }
    fclose(fp);
}
