#ifndef __TEXT_PICTURE_MANAGER_H__
#define __TEXT_PICTURE_MANAGER_H__

#include <stdio.h>
#include "Models.h"

TextPicture* allocateTextPicture();
void freeTextPicture(TextPicture *picture);

TextPicture createTestTextPicture();
void clearTestTextPicture(TextPicture picture);


#endif
