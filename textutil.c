#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "textutil.h"

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}

void remove_punctuation_and_digits(char *str) {
    int i, j = 0;
    char temp[1000];
    for (i = 0; str[i]; i++) {
        if (isalpha(str[i]) || str[i] == ' ')
            temp[j++] = str[i];
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

void extract_valid_sections(char *line, int *isTitle, int *isBody, int *skipURL) {
    if (strstr(line, "<url>")) *skipURL = 1;
    if (strstr(line, "</url>")) *skipURL = 0;

    if (strstr(line, "<title>")) *isTitle = 1;
    if (strstr(line, "</title>")) *isTitle = 0;

    if (strstr(line, "<body>")) *isBody = 1;
    if (strstr(line, "</body>")) *isBody = 0;
}

void process_line(char *line, int *isTitle, int *isBody, int *skipURL) {
    extract_valid_sections(line, isTitle, isBody, skipURL);

    if (*skipURL) return;
    if (!(*isTitle) && !(*isBody)) return;

    remove_punctuation_and_digits(line);
    to_lowercase(line);
}
