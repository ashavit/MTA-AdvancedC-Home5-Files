
#include <stdlib.h>
#include <string.h>
#include "PicListManager.h"

static PicListNode* allocateListNode(char data, int x, int y);

static void addToEmptyList(PicList *list, PicListNode *node);
static void addToBeginningOfList(PicList *list, PicListNode *node);
static void addToEndOfList(PicList *list, PicListNode *node);
static void addInsideList(PicListNode *prev, PicListNode *node);
static PicListNode* findPlaceToInsertChar(PicList *list, int x, int y);

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

void printPicList(PicList list)
{
    PicListNode *cur = list.head;
    while (cur)
    {
        printf("Pic char: %c (%d), at %d,%d\n", cur->data.ch, cur->data.ch, cur->data.position.x, cur->data.position.y);
        cur = cur->next;
    }
}

void addPicListChar(PicList *list, char data, int x, int y)
{
    PicListNode *node = allocateListNode(data, x, y);
    PicListNode *prev = NULL;

    if (!list->head)
        addToEmptyList(list, node);
    else
    {
        prev = findPlaceToInsertChar(list, x, y);
        if (!prev)
            addToBeginningOfList(list, node);
        else if (prev == list->tail)
            addToEndOfList(list, node);
        else if (prev->next->data.position.x == x && prev->next->data.position.y == y)
        {
            // Override char in place and release unused node
            // printf("Override char at %d,%d\n", x,y);
            prev->next->data.ch = data;
            free(node);
        }
        else
            addInsideList(prev, node);
    }
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

static void addToBeginningOfList(PicList *list, PicListNode *node)
{
    node->next = list->head;
    list->head = node;
}

static void addToEndOfList(PicList *list, PicListNode *node)
{
    list->tail->next = node;
    list->tail = node;
}

static void addInsideList(PicListNode *prev, PicListNode *node)
{
    node->next = prev->next;
    prev->next = node;
}

static PicListNode* findPlaceToInsertChar(PicList *list, int x, int y)
{
    PicListNode *cur = list->head;
    PicListNode *prev = NULL;

    while (cur && (cur->data.position.y < y ||
                   (cur->data.position.y == y && cur->data.position.x < x)))
    {
      prev = cur;
      cur = cur->next;
    }
    return prev;
}
