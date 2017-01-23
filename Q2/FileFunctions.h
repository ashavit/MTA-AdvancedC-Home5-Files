#ifndef __FILE_FUNCTIONS_H__
#define __FILE_FUNCTIONS_H__

#include <stdio.h>

FILE* openFile(const char* fileName, char *rights);
void closeFile(FILE *filePtr);

unsigned int binReadString(char* string, unsigned int size, FILE *filePtr);
unsigned int binReadInt(int* num, unsigned int size, FILE *filePtr);
unsigned int binReadUnsignedInt(unsigned int* num, unsigned int size, FILE *filePtr);
unsigned int binReadFloat(float* num, unsigned int size, FILE *filePtr);

unsigned int binWriteString(char* string, unsigned int size, FILE *filePtr);
unsigned int binWriteInt(int num, FILE *filePtr);
unsigned int binWriteUnsignedInt(unsigned int num, FILE *filePtr);
unsigned int binWriteFloat(float num, FILE *filePtr);

void writeStringLine(const char* string, FILE *filePtr);

#endif
