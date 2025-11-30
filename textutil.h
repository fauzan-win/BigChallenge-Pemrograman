#ifndef TEXTUTIL_H
#define TEXTUTIL_H

void clean_string(char *str);
void to_lowercase(char *str);
void remove_punctuation_and_digits(char *str);
void extract_valid_sections(char *line, int *isTitle, int *isBody, int *skipURL);
void process_line(char *line, int *isTitle, int *isBody, int *skipURL);

#endif
