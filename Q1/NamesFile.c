#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "NamesFile.h"
#include "FileFunctions.h"

static char** allocateNamesArray(unsigned int size);
static char* allocateString(unsigned int size);
static void removeCapitalLettersFromName(char *str);
static void merge(char **array, int left, int mid, int right);
static void mergeSort(char **array, int left, int right);

char** readBinaryNamesFile(const char* fileName, unsigned int count)
{
    FILE *input = openFile(fileName, "rb");

    /// TODO: Dynamic alloc resizing
    char **array = allocateNamesArray(count);

    unsigned int size;
    for (int i = 0; i < count; ++i)
    {
        binReadInt(&size, 1, input);
        array[i] = allocateString(size);
        binReadString(array[i], size, input);
    }

    closeFile(input);
    return array;
}

void saveNamesFile(const char *baseName, char **names, unsigned int size)
{
    char *textNameFile = allocateString(strlen(baseName) + 5);
    sprintf(textNameFile, "%s%s", baseName, ".txt");

    FILE *save = openFile(textNameFile, "w");

    for (int i = 0; i < size; ++i)
    {
        writeStringLine(names[i], save);
    }

    closeFile(save);
}

void removeCapitalLetters(char **array, unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        removeCapitalLettersFromName(array[i]);
    }
}

void sortNames(char **array, int size)
{
    mergeSort(array, 0, size - 1);
}

void printNames(char **array, unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%s\n", array[i]);
    }
    printf("\n");
}

void freeNames(char **array, unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
}

////////////////////////////////////

static char** allocateNamesArray(unsigned int size)
{
    char **array = (char**)malloc(sizeof(char*) * 10);
    if (!array)
    {
        printf("Error malloc");
        exit(MALLOC_ERROR);
    }
    return array;
}

static char* allocateString(unsigned int size)
{
    char *string = (char*)malloc(sizeof(char) * size);
    if (!string)
    {
        printf("Error malloc");
        exit(MALLOC_ERROR);
    }
    return string;
}

static void removeCapitalLettersFromName(char *str)
{
    int read = 0, write = 0;

	while (str[read] != '\0')
	{
		if (str[read] >= 'a' && str[read] <= 'z')
		{
            if (write < read)
                str[write] = str[read];

			write++;
		}
        read++;
	}
    // End string
	str[write] = '\0';
}

static void merge(char **array, int left, int mid, int right)
{
    char **temp = allocateNamesArray(right - left + 1);

    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (strcmp(array[i], array[j]) < 0)
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    while (i <= mid)
        temp[k++] = array[i++];

    while (j <= right)
        temp[k++] = array[j++];

    while (k--, k >= 0)
        array[left + k] = temp[k];

    free(temp);
}

static void mergeSort(char **array, int left, int right)
{
    if (right <= left)
        return;

    int mid = (right - left) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}
