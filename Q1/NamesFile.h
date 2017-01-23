#ifndef __NAMES_FILE_H__
#define __NAMES_FILE_H__

#include <stdio.h>

char** readBinaryNamesFile(const char* fileName, unsigned int count);
void saveNamesFile(const char *baseName, char **names, unsigned int namesCount);

void removeCapitalLetters(char **array, unsigned int size);
void sortNames(char **array, int size);
void printNames(char **array, unsigned int size);

void freeNames(char **array, unsigned int size);

#endif
