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
    addPicListChar(&picture.pic, '$', 2, 4);
    addPicListChar(&picture.pic, '#', 1, 3);
    addPicListChar(&picture.pic, '$', 2, 2);
    addPicListChar(&picture.pic, '#', 2, 3);
    return picture;
}

void clearTestTextPicture(TextPicture picture)
{
    clearPicList(picture.pic);
}
