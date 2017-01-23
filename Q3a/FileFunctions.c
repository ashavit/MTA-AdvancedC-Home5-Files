
#include <stdlib.h>
#include <string.h>
#include "FileFunctions.h"

#define READ_FILE_ERROR 2
#define WRITE_FILE_ERROR 3


FILE* openFile(const char* fileName, char *rights)
{
    FILE *filePtr = fopen(fileName, rights);
    if (!filePtr)
    {
        printf("Error opening file\n");
        exit(READ_FILE_ERROR);
    }
    return filePtr;
}

void closeFile(FILE *filePtr)
{
    fclose(filePtr);
}

unsigned int binReadString(char* string, unsigned int size, FILE *filePtr)
{
    if (fread(string, sizeof(char), size, filePtr) != size)
    {
        printf("Error reading string file\n");
        exit(READ_FILE_ERROR);
    }
    return size;
}

unsigned int binReadInt(int* num, unsigned int size, FILE *filePtr)
{
    if (fread(num, sizeof(int), size, filePtr) != size)
    {
        printf("Error reading int from file\n");
        exit(READ_FILE_ERROR);
    }
    return size;
}

unsigned int binReadUnsignedInt(unsigned int* num, unsigned int size, FILE *filePtr)
{
    if (fread(num, sizeof(int), size, filePtr) != size)
    {
        printf("Error reading unsigned int from file\n");
        exit(READ_FILE_ERROR);
    }
    return size;
}

unsigned int binReadFloat(float* num, unsigned int size, FILE *filePtr)
{
    if (fread(num, sizeof(float), size, filePtr) != size)
    {
        printf("Error reading float from file\n");
        exit(READ_FILE_ERROR);
    }
    return size;
}

unsigned int binWriteString(char* string, unsigned int size, FILE *filePtr)
{
    if (fwrite(string, sizeof(char), size, filePtr) != size)
    {
        printf("Error writing string to file\n");
        exit(WRITE_FILE_ERROR);
    }
    return size;
}

unsigned int binWriteInt(int num, FILE *filePtr)
{
    int size = 1;
    if (fwrite(&num, sizeof(int), size, filePtr) != size)
    {
        printf("Error writing int to file\n");
        exit(WRITE_FILE_ERROR);
    }
    return size;
}

unsigned int binWriteUnsignedInt(unsigned int num, FILE *filePtr)
{
    int size = 1;
    if (fwrite(&num, sizeof(unsigned int), size, filePtr) != size)
    {
        printf("Error writing unsigned int to file\n");
        exit(WRITE_FILE_ERROR);
    }
    return size;
}

unsigned int binWriteFloat(float num, FILE *filePtr)
{
    int size = 1;
    if (fwrite(&num, sizeof(float), size, filePtr) != size)
    {
        printf("Error writing float to file\n");
        exit(WRITE_FILE_ERROR);
    }
    return size;
}

void writeStringLine(const char* string, FILE *filePtr)
{
    fprintf(filePtr, "%s", string);
}

void writeChar(const char ch, FILE *filePtr)
{
    fputs(&ch, filePtr);
}
