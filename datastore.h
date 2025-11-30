#ifndef DATASTORE_H
#define DATASTORE_H

#define MAX_WORDS 50000
#define MAX_LEN   100

typedef struct {
    char word[MAX_LEN];
    int freq;
    int length;
} Word;

typedef struct {
    char letter;     
    int count;       
    Word list[MAX_WORDS];
} LetterGroup;

void init_groups(LetterGroup groups[]);
void add_word(LetterGroup groups[], char *token);
void sort_groups(LetterGroup groups[]);
void sort_single_group(Word arr[], int n);

void save_binary(const char *filename, LetterGroup groups[]);
void load_binary(const char *filename, LetterGroup groups[]);
void display_top_n(LetterGroup groups[], int n);

#endif
