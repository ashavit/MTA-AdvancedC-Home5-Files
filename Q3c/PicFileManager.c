#include <stdlib.h>
#include <string.h>

#include "PicFileManager.h"
#include "PicListManager.h"
#include "TextPictureManager.h"
#include "FileFunctions.h"

static char** allocateStringRowArray(unsigned int size);
static char* allocateString(unsigned int size);
static char* allocateSpacesString(unsigned int size);
static void freeStringRowArray(char** array, unsigned int size);
static void readPicCharsFromString(PicList *list, char *string, int row);
static void getPictureSize(FILE *filePtr, int *rows, int *cols, int *fileLength);

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

TextPicture * openTextPicture(char* fileName)
{
    FILE *input = openFile(fileName, "r");
    int lineLength;

    TextPicture *picture = allocateTextPicture();
    getPictureSize(input, &picture->numRows, &picture->numCols, &lineLength);
    // printf("I got %d rows, and %d cols, with line length %d\n", picture->numRows, picture->numCols, lineLength);

    char *row = allocateString(lineLength + 1);
    for (int i = 0; i < picture->numRows; ++i)
    {
        readStringLine(row, lineLength + 1, input); /* Read line until \n or full fileSize */
        readPicCharsFromString(&picture->pic, row, i);
    }

    free(row);
    closeFile(input);

    return picture;
}

void replicatePicture(TextPicture srcPic, int m, int n, char* repPicFileName)
{
    int row, col;
    int multiCols = srcPic.numCols * n;
    int multiRows = srcPic.numRows * m;
    char **rows = allocateStringRowArray(multiRows);
    // printf("I got %d rows, and %d cols\n", multiRows, multiCols);

    for (row = 0; row < multiRows; ++row)
        rows[row] = allocateSpacesString(multiCols);

    PicListNode *cur = srcPic.pic.head;
    int copyX, copyY;
    while (cur)
    {
        // Ovewrride spaces with chars in place, for all replicated pictures
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                copyY = cur->data.position.y + srcPic.numRows * j;
                copyX = cur->data.position.x + srcPic.numCols * i;
                // printf("put %c from %d,%d at %d,%d\n", cur->data.ch, cur->data.position.y, cur->data.position.x, copyY, copyX);
                rows[copyX][copyY] = cur->data.ch;
            }
        }
        cur = cur->next;
    }

    // Save to painting to file
    FILE *filePtr = openFile(repPicFileName, "w+");
    for (row = 0; row < multiRows; ++row)
        writeStringLine(rows[row], filePtr);

    freeStringRowArray(rows, multiRows);
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

static void readPicCharsFromString(PicList *list, char *string, int row)
{
    int i = 0;
    while (string[i] != '\n')
    {
        if (string[i] > ' ')
            addPicListChar(list, string[i], row, i);
        ++i;
    }
}

static void getPictureSize(FILE *filePtr, int *rows, int *cols, int *fileLength)
{
    unsigned long fileSize = getFileSize(filePtr);
    *fileLength = fileSize;
    gotoFileStart(filePtr);
    // printf("I got %ld size\n", fileSize);

    char *firstRow = allocateString((int)fileSize);
    readStringLine(firstRow, (int)fileSize, filePtr);
    // printf("read line: %s\n", firstRow);;

    int lineLength = strlen(firstRow);
    *rows = fileSize / lineLength;
    int i = lineLength - 1;
    while (firstRow[i] < ' ') /* Find any new lines, CR, End, etc. */
        --i;

    *cols = i + 1;
    free(firstRow);
    gotoFileStart(filePtr);
}
