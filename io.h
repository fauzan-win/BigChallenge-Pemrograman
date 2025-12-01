#ifndef IO_H
#define IO_H

#include "process.h"

void saveToBinary(const char *filename, WordData *wd);
void displayTopN(WordData *wd, int n);

#endif
