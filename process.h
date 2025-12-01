#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    char word[100];
    int count;
} WordFreq;

typedef struct {
    WordFreq *words;
    int count;
    int capacity;
} WordData;

// fungsi-fungsi
void initWordData(WordData *wd);
void ensureCapacity(WordData *wd);
void cleanWord(char *str);
void addWord(WordData *wd, const char *word);
int containsURL(const char *line);
void loadAndProcessText(const char *filename, WordData *wd);
void sortWords(WordData *wd);

#endif
