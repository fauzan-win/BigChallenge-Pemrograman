#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "datastore.h"

void init_groups(LetterGroup groups[]) {
    for (int i = 0; i < 26; i++) {
        groups[i].letter = 'a' + i;
        groups[i].count = 0;
    }
}

void add_word(LetterGroup groups[], char *token) {
    if (!isalpha(token[0])) return;

    int idx = token[0] - 'a';

    // cek apakah sudah ada
    for (int i = 0; i < groups[idx].count; i++) {
        if (strcmp(groups[idx].list[i].word, token) == 0) {
            groups[idx].list[i].freq++;
            return;
        }
    }

    // tambah baru
    strcpy(groups[idx].list[groups[idx].count].word, token);
    groups[idx].list[groups[idx].count].freq = 1;
    groups[idx].list[groups[idx].count].length = strlen(token);
    groups[idx].count++;
}

void sort_single_group(Word arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            int swap = 0;

            if (arr[j].freq < arr[j+1].freq)
                swap = 1;
            else if (arr[j].freq == arr[j+1].freq &&
                     arr[j].length < arr[j+1].length)
                swap = 1;
            else if (arr[j].freq == arr[j+1].freq &&
                     arr[j].length == arr[j+1].length &&
                     strcmp(arr[j].word, arr[j+1].word) < 0)
                swap = 1;

            if (swap) {
                Word temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void sort_groups(LetterGroup groups[]) {
    for (int i = 0; i < 26; i++) {
        sort_single_group(groups[i].list, groups[i].count);
    }
}

void save_binary(const char *filename, LetterGroup groups[]) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return;

    for (int i = 0; i < 26; i++) {
        fwrite(&groups[i].letter, sizeof(char), 1, fp);
        fwrite(&groups[i].count, sizeof(int), 1, fp);

        for (int j = 0; j < groups[i].count; j++) {
            int len = groups[i].list[j].length;
            fwrite(&len, sizeof(int), 1, fp);
            fwrite(groups[i].list[j].word, sizeof(char), len, fp);
            fwrite(&groups[i].list[j].freq, sizeof(int), 1, fp);
        }
    }

    fclose(fp);
}

void load_binary(const char *filename, LetterGroup groups[]) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;

    for (int i = 0; i < 26; i++) {

        fread(&groups[i].letter, sizeof(char), 1, fp);
        fread(&groups[i].count, sizeof(int), 1, fp);

        for (int j = 0; j < groups[i].count; j++) {
            int len;
            fread(&len, sizeof(int), 1, fp);

            fread(groups[i].list[j].word, sizeof(char), len, fp);
            groups[i].list[j].word[len] = '\0';

            groups[i].list[j].length = len;

            fread(&groups[i].list[j].freq, sizeof(int), 1, fp);
        }
    }
    fclose(fp);
}

void display_top_n(LetterGroup groups[], int n) {
    for (int i = 0; i < 26; i++) {
        printf("%c {", groups[i].letter);

        for (int j = 0; j < n && j < groups[i].count; j++) {
            printf("%s (%d)", groups[i].list[j].word, groups[i].list[j].freq);
            if (j < n - 1 && j < groups[i].count - 1) printf(", ");
        }

        printf("}\n");
    }
}
