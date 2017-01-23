#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "TextPictureManager.h"
#include "PicListManager.h"
#include "PicFileManager.h"

int main(int argc, char **argv)
{
    TextPicture *picture = openTextPicture("big.txt");
    // printPicList(picture->pic);

    mergePictures(picture, "small.txt");
    printf("big after merge:\n" );
    printPicList(picture->pic);

    paintTextPicture(*picture, "merged.txt");

    freeTextPicture(picture);
    return 0;
}
