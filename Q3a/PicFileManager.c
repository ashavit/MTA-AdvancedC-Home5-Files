#include <stdlib.h>
#include <string.h>

#include "PicFileManager.h"
#include "PicListManager.h"
#include "FileFunctions.h"

static char** allocateStringRowArray(unsigned int size);
static char* allocateString(unsigned int size);
static char* allocateSpacesString(unsigned int size);
static void freeStringRowArray(char** array, unsigned int size);

void paintTextPicture(TextPicture textPic, char* filename)
{
    int row, col;
    char **rows = allocateStringRowArray(textPic.numRows);

    for (row = 0; row < textPic.numRows; ++row)
        rows[row] = allocateSpacesString(textPic.numCols);

    PicListNode *cur = textPic.pic.head;
    while (cur)
    {
        // Ovewrride spaces with chars in place
        rows[cur->data.position.y][cur->data.position.x] = cur->data.ch;
        cur = cur->next;
    }

    // Save to painting to file
    FILE *filePtr = openFile(filename, "w");
    for (row = 0; row < textPic.numRows; ++row)
        writeStringLine(rows[row], filePtr);

    freeStringRowArray(rows, textPic.numRows);
    closeFile(filePtr);
}


static char** allocateStringRowArray(unsigned int size)
{
    char **array = (char**)malloc(sizeof(char*) * size);
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

static char* allocateSpacesString(unsigned int size)
{
    // Create line with full spaces
    char *string = allocateString(size + 1);
    for (int i = 0; i < size; ++i)
    {
        string[i] = ' ';
    }
    string[size] = '\n';

    return string;
}

static void freeStringRowArray(char** array, unsigned int size)
{
    if (!array)
        return;

    for (int i = 0; i < size; ++i)
    {
        free(array[i]);
    }
    free(array);
}
