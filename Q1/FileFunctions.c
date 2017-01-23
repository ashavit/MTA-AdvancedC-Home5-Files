
#include <stdlib.h>
#include "Constants.h"
#include "FileFunctions.h"

#define READ_FILE_ERROR 2
#define WRITE_FILE_ERROR 3


FILE* openFile(const char* fileName, char *rights)
{
    FILE *filePtr = fopen(fileName, rights);
    if (!filePtr)
    {
        printf("Error opening file");
        exit(READ_FILE_ERROR);
    }
    return filePtr;
}

void closeFile(FILE *filePtr)
{
    fclose(filePtr);
}

void binReadString(char* string, unsigned int size, FILE *filePtr)
{
    if (fread(string, sizeof(char), size, filePtr) != size)
    {
        printf("Error reading file");
        exit(READ_FILE_ERROR);
    }
}

void binReadInt(unsigned int* num, unsigned int size, FILE *filePtr)
{
    if (fread(num, sizeof(int), size, filePtr) != size)
    {
        printf("Error reading file");
        exit(READ_FILE_ERROR);
    }
}

void writeStringLine(const char* string, FILE *filePtr)
{
    fprintf(filePtr, "%s\n", string);
}
