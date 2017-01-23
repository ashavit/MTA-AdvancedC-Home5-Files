
#include <stdlib.h>
#include <string.h>
#include "PicListManager.h"

static PicListNode* allocateListNode(char data, int x, int y);

static void addToEmptyList(PicList *list, PicListNode *node);
static void addToEndOfList(PicList *list, PicListNode *cell);


PicList createPicList()
{
    PicList res;
    res.head = res.tail = NULL;
    return res;
}

void clearPicList(PicList list)
{
    PicListNode *node = list.head;
    PicListNode *next = node;
    while (node)
    {
        next = node->next;
        free(next);
        node = next;
    }
}

void addPicListChar(PicList *list, char data, int x, int y)
{
    PicListNode *node = allocateListNode(data, x, y);
    PicListNode *prev = NULL;

    if (!list->head)
        addToEmptyList(list, node);
    else
        addToEndOfList(list, node);
}

static PicListNode* allocateListNode(char data, int x, int y)
{
    PicListNode *res = (PicListNode*)malloc(sizeof(PicListNode));
    if (!res)
    {
        printf("Malloc error\n");
        exit(MALLOC_ERROR);
    }
    res->data.ch = data;
    res->data.position.x = x;
    res->data.position.y = y;
    res->next = NULL;
    return res;
}

static void addToEmptyList(PicList *list, PicListNode *node)
{
    list->head = list->tail = node;
}

static void addToEndOfList(PicList *list, PicListNode *cell)
{
    list->tail->next = cell;
    list->tail = cell;
}
