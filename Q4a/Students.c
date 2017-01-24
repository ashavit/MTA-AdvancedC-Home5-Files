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

static GradeIndexList sortIndexStudentsByGrade(FILE *input, short int size);
static void printGradeIndexList(GradeIndexList list);
static void addGradeIndex(GradeIndexList *list, int avg, unsigned int index);
static void addToEmptyList(GradeIndexList *list, GradeIndexNode *node);
static void addToBeginningOfList(GradeIndexList *list, GradeIndexNode *node);
static void addToEndOfList(GradeIndexList *list, GradeIndexNode *node);
static void addInsideList(GradeIndexNode *prev, GradeIndexNode *node);
static GradeIndexNode* findPlaceToInsertGrade(GradeIndexList *list, int avg);

void sortStudentIndexesForFile(const char* fileName)
{
	// Load bin data file
    FILE *input = openFile(fileName, "rb");
    short int studentCount;
    binReadShortInt(&studentCount, 1, input);

    GradeIndexList list = sortIndexStudentsByGrade(input, studentCount);
    printGradeIndexList(list);
    closeFile(input);

    char *indexFileName = allocateString(strlen(fileName) + 5);
    sprintf(indexFileName, "%s%s", fileName, ".ind");
    FILE *output = openFile(indexFileName, "wb");
	free(indexFileName);

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
        printf("Error malloc");
        exit(MALLOC_ERROR);
    }
    return string;
}
