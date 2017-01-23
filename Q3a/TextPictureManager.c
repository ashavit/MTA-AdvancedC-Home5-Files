#include <stdlib.h>
#include <string.h>

#include "TextPictureManager.h"
#include "PicListManager.h"

TextPicture createTestTextPicture()
{
    TextPicture picture;
    picture.numRows = 5;
    picture.numCols = 8;
    picture.pic = createPicList();
    addPicListChar(&picture.pic, '$', 4, 2);
    addPicListChar(&picture.pic, '#', 3, 1);
    addPicListChar(&picture.pic, '$', 2, 2);
    addPicListChar(&picture.pic, '#', 3, 2);
    return picture;
}

void clearTestTextPicture(TextPicture picture)
{
    clearPicList(picture.pic);
}
