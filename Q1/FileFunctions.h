#ifndef __FILE_FUNCTIONS_H__
#define __FILE_FUNCTIONS_H__

#include <stdio.h>

FILE* openFile(const char* fileName, char *rights);
void closeFile(FILE *filePtr);

void binReadString(char* string, unsigned int size, FILE *filePtr);
void binReadInt(unsigned int* num, unsigned int size, FILE *filePtr);

void writeStringLine(const char* string, FILE *filePtr);

#endif
