#ifndef __PIC_LIST_MANAGER_H__
#define __PIC_LIST_MANAGER_H__

#include <stdio.h>
#include "Models.h"

PicList createPicList();
void clearPicList(PicList list);

void addPicListChar(PicList *list, char data, int x, int y);

#endif
