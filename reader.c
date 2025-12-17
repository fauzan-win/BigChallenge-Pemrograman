#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "word.h"

LetterGroup groups[26];
int binary_saved = 0;

void init_groups() {
    for (int i = 0; i < 26; i++) {
        groups[i].letter = 'a' + i;
        groups[i].count = 0;
    }
}

static void clean_string(char *s) {
    int j = 0;
    for (int i = 0; s[i]; i++) {
        if (isalpha((unsigned char)s[i]))
            s[j++] = tolower((unsigned char)s[i]);
        else if (isspace((unsigned char)s[i]))
            s[j++] = ' ';
    }
    s[j] = '\0';
}

static void add_word(const char *token) {
    if (!isalpha((unsigned char)token[0])) return;
    int idx = token[0] - 'a';
    if (idx < 0 || idx >= 26) return;

    LetterGroup *g = &groups[idx];
    for (int i = 0; i < g->count; i++) {
        if (strcmp(g->words[i].word, token) == 0) {
            g->words[i].freq++;
            return;
        }
    }
    if (g->count >= MAX_PER_LETTER) return;

    strcpy(g->words[g->count].word, token);
    g->words[g->count].freq = 1;
    g->words[g->count].length = strlen(token);
    g->count++;
}

void read_text_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Gagal membuka file input!\n");
        exit(1);
    }

    char line[8192];
    int skip_url = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "<url")) skip_url = 1;
        if (strstr(line, "</url>")) { skip_url = 0; continue; }
        if (skip_url) continue;

        clean_string(line);
        char *token = strtok(line, " \t\n");
        while (token) {
            add_word(token);
            token = strtok(NULL, " \t\n");
        }
    }
    fclose(fp);

    for (int i = 0; i < 26; i++) sort_words(&groups[i]);
}
