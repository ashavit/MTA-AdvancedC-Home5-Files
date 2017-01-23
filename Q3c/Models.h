#ifndef __MODELS_H__
#define __MODELS_H__

#define MAIN_ARGS_ERROR -1
#define MALLOC_ERROR 1

typedef struct _point
{
	int x;
	int y;
} Point;

typedef struct _picChar
{
	Point position;
	char ch;
} PicChar;


typedef struct _picListNode
{
	PicChar data;
	struct _picListNode* next;
} PicListNode;

typedef struct _picList
{
	PicListNode* head;
	PicListNode* tail;
} PicList;


typedef struct _textPicture
{
	int numRows;
	int numCols;
	PicList pic;
} TextPicture;

#endif
