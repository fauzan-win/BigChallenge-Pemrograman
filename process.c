#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "process.h"

void initWordData(WordData *wd) {
    wd->count = 0;
    wd->capacity = 5000;
    wd->words = malloc(sizeof(WordFreq) * wd->capacity);
}

void ensureCapacity(WordData *wd) {
    if (wd->count >= wd->capacity) {
        wd->capacity *= 2;
        wd->words = realloc(wd->words, sizeof(WordFreq) * wd->capacity);
    }
}

void cleanWord(char *str) {
    char temp[100];
    int j = 0;

    for (int i = 0; str[i]; i++) {
        if (isalpha((unsigned char)str[i])) {
            temp[j++] = tolower(str[i]);
        }
    }

    temp[j] = '\0';
    strcpy(str, temp);
}

void addWord(WordData *wd, const char *word) {
    if (strlen(word) == 0) return;

    for (int i = 0; i < wd->count; i++) {
        if (strcmp(wd->words[i].word, word) == 0) {
            wd->words[i].count++;
            return;
        }
    }

    ensureCapacity(wd);

    strcpy(wd->words[wd->count].word, word);
    wd->words[wd->count].count = 1;
    wd->count++;
}

int containsURL(const char *line) {
    return strstr(line, "<url>") != NULL;
}

void loadAndProcessText(const char *filename, WordData *wd) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("File tidak ditemukan: %s\n", filename);
        return;
    }

    char line[16384];

    while (fgets(line, sizeof(line), f)) {

        if (containsURL(line)) continue;

        char *token = strtok(line, " \t\n\r");
        while (token) {
            char word[100];
            strcpy(word, token);

            cleanWord(word);
            addWord(wd, word);

            token = strtok(NULL, " \t\n\r");
        }
    }

    fclose(f);
}

int cmpWords(const void *a, const void *b) {
    return strcmp(((WordFreq*)a)->word, ((WordFreq*)b)->word);
}

void sortWords(WordData *wd) {
    qsort(wd->words, wd->count, sizeof(WordFreq), cmpWords);
}
