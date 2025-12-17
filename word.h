#ifndef WORD_H
#define WORD_H

#define MAX_WORD 50
#define MAX_PER_LETTER 5000

typedef struct {
    char word[MAX_WORD];
    int freq;
    int length;
} Word;

typedef struct {
    char letter;
    Word words[MAX_PER_LETTER];
    int count;
} LetterGroup;

extern LetterGroup groups[26];
extern int binary_saved;

void init_groups();
void sort_words(LetterGroup *g);

#endif
