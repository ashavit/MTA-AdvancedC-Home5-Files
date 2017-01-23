#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "TextPictureManager.h"
#include "PicListManager.h"
#include "PicFileManager.h"

int main(int argc, char **argv)
{
    TextPicture *picture = openTextPicture("Exe5Q4-B.txt");

    printf("Final sorted List:\n");
    printPicList(picture->pic);

    freeTextPicture(picture);
    return 0;
}
