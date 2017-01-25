#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "Students.h"
#include "FileFunctions.h"

typedef struct _gradeIndexNode
{
	int avg;
    unsigned int index;
	struct _gradeIndexNode* next;
} GradeIndexNode;

typedef struct _gradeIndexList
{
	GradeIndexNode* head;
	GradeIndexNode* tail;
} GradeIndexList;


static GradeIndexList createGradeIndexList();
static void clearGradeIndexList(GradeIndexList list);
static GradeIndexNode* allocateListNode(int avg, unsigned int index);
static char* allocateString(unsigned int size);
static char** allocateStringArray(unsigned int size);
static void reallocateStringArray(char*** array, unsigned int size);

static void addStringToStringArray(char *string, char*** array, unsigned int *size, unsigned int *memSize);
static void doubleStringArray(char*** array, unsigned int *size);

static GradeIndexList sortIndexStudentsByGrade(FILE *input, short int size);
static void printGradeIndexList(GradeIndexList list);
static void addGradeIndex(GradeIndexList *list, int avg, unsigned int index);
static void addToEmptyList(GradeIndexList *list, GradeIndexNode *node);
static void addToBeginningOfList(GradeIndexList *list, GradeIndexNode *node);
static void addToEndOfList(GradeIndexList *list, GradeIndexNode *node);
static void addInsideList(GradeIndexNode *prev, GradeIndexNode *node);
static GradeIndexNode* findPlaceToInsertGrade(GradeIndexList *list, int avg);
static FILE* getIndexFileForDataBase(const char* dbFileName, char *rights);

void sortStudentIndexesForFile(const char* fileName)
{
	// Load bin data file
    FILE *input = openFile(fileName, "rb");
    short int studentCount;
    binReadShortInt(&studentCount, 1, input);

    GradeIndexList list = sortIndexStudentsByGrade(input, studentCount);
    printGradeIndexList(list);
    closeFile(input);

    FILE *output = getIndexFileForDataBase(fileName, "wb");

	// Save indexes to index bin file
    GradeIndexNode *node = list.head;
    while (node)
    {
        binWriteUnsignedInt(node->index, output);
        node = node->next;
    }

    clearGradeIndexList(list);
    closeFile(output);
}

char ** findAverageGrade(char* database, int avgGrade, int * resSize)
{
	// Load bin data file
    FILE *dbFile = openFile(database, "rb");

	// Get student max count
    short int studentCount;
    binReadShortInt(&studentCount, 1, dbFile);

	// Load index data file
	FILE *indexFile = getIndexFileForDataBase(database, "rb");

	unsigned int index;
	short int nameLength;
	int avg = 0;
	unsigned int arrSize = 0, memSize = 0;
	char **result = NULL;
	for (int i = 0; i < studentCount && avg <= avgGrade; ++i)
	{
		binReadUnsignedInt(&index, 1, indexFile); /*Get next sorted index */
		fseek(dbFile, index, SEEK_SET); /* Skip to student by sorted index */
		binReadShortInt(&nameLength, 1, dbFile); /* Read student name length */
        fseek(dbFile, nameLength, SEEK_CUR); /* Skip name to check grade */
        binReadInt(&avg, 1, dbFile); /* Read student grade */

		if (avg == avgGrade)
		{
			fseek(dbFile, -(sizeof(int) + nameLength), SEEK_CUR); /* Rewind back name and grade */
			char *name = allocateString(nameLength + 1);
			binReadString(name, nameLength, dbFile);
			name[nameLength] = '\0';

			addStringToStringArray(name, &result, &arrSize, &memSize);
		}
	}

	*resSize = arrSize;
	return result;
}

static FILE* getIndexFileForDataBase(const char* dbFileName, char *rights)
{
    char *indexFileName = allocateString(strlen(dbFileName) + 5);
    sprintf(indexFileName, "%s%s", dbFileName, ".ind");
    FILE *res = openFile(indexFileName, rights);
	free(indexFileName);
	return res;
}

static GradeIndexList sortIndexStudentsByGrade(FILE *input, short int size)
{
    GradeIndexList list = createGradeIndexList();
    unsigned int index = sizeof(short int); /* start after the student count byte */
    short int nameLength;
    int avg;

    for (int i = 0; i < size; ++i)
    {
        // Get name length and skip name
        binReadShortInt(&nameLength, 1, input);
        fseek(input, nameLength, SEEK_CUR);
        binReadInt(&avg, 1, input);
        printf("Student %d at index %d has %d grade\n", i, index, avg);

        addGradeIndex(&list, avg, index);
        index += (sizeof(short int) + nameLength + sizeof(int));
    }
    return list;
}

static GradeIndexList createGradeIndexList()
{
    GradeIndexList list;
    list.head = list.tail = NULL;
    return list;
}

static void clearGradeIndexList(GradeIndexList list)
{
    GradeIndexNode *cur = list.head;
    GradeIndexNode *next;

    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

static GradeIndexNode* allocateListNode(int avg, unsigned int index)
{
    GradeIndexNode *res = (GradeIndexNode*)malloc(sizeof(GradeIndexNode));
    if (!res)
    {
        printf("Malloc error\n");
        exit(MALLOC_ERROR);
    }
    res->avg = avg;
    res->index = index;
    res->next = NULL;
    return res;
}

static void addGradeIndex(GradeIndexList *list, int avg, unsigned int index)
{
    GradeIndexNode *node = allocateListNode(avg, index);
    GradeIndexNode *prev = NULL;

    if (!list->head)
        addToEmptyList(list, node);
    else
    {
        prev = findPlaceToInsertGrade(list, avg);
        if (!prev)
            addToBeginningOfList(list, node);
        else if (prev == list->tail)
            addToEndOfList(list, node);
        else
            addInsideList(prev, node);
    }
}

static void printGradeIndexList(GradeIndexList list)
{
    GradeIndexNode *cur = list.head;
    while (cur)
    {
        printf("Student with grade %d @ index %d\n", cur->avg, cur->index);
        cur = cur->next;
    }
}

static void addToEmptyList(GradeIndexList *list, GradeIndexNode *node)
{
    list->head = list->tail = node;
}

static void addToBeginningOfList(GradeIndexList *list, GradeIndexNode *node)
{
    node->next = list->head;
    list->head = node;
}

static void addToEndOfList(GradeIndexList *list, GradeIndexNode *node)
{
    list->tail->next = node;
    list->tail = node;
}

static void addInsideList(GradeIndexNode *prev, GradeIndexNode *node)
{
    node->next = prev->next;
    prev->next = node;
}

static GradeIndexNode* findPlaceToInsertGrade(GradeIndexList *list, int avg)
{
    GradeIndexNode *cur = list->head;
    GradeIndexNode *prev = NULL;

    while (cur && cur->avg < avg)
    {
      prev = cur;
      cur = cur->next;
    }
    return prev;
}

static char* allocateString(unsigned int size)
{
    char *string = (char*)malloc(sizeof(char) * size);
    if (!string)
    {
        printf("Error malloc\n");
        exit(MALLOC_ERROR);
    }
    return string;
}

static char** allocateStringArray(unsigned int size)
{
	char **array = (char**)malloc(sizeof(char*));
	if (!array)
	{
		printf("Error Malloc\n");
		exit(MALLOC_ERROR);
	}
	return array;
}

static void reallocateStringArray(char*** array, unsigned int size)
{
	char **newPtr = (char**)realloc(*array, sizeof(char*) * size);
	if (!newPtr)
	{
		printf("Error Realloc\n");
		exit(MALLOC_ERROR);
	}
	*array = newPtr;
}

static void addStringToStringArray(char *string, char*** array, unsigned int *size, unsigned int *memSize)
{
	if (*memSize == 0)
	{
		*memSize = 1;
		*array = allocateStringArray(*memSize);
	}
	else if (*size == *memSize)
	{
		doubleStringArray(array, memSize);
	}
	*array[(*size)++] = string;
}

static void doubleStringArray(char*** array, unsigned int *size)
{
	int newSize = *size * 2;
	reallocateStringArray(array, newSize);
	*size = newSize;
}
