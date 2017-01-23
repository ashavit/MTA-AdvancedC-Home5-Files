#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "TextPictureManager.h"
#include "PicListManager.h"
#include "PicFileManager.h"

int main(int argc, char **argv)
{
    TextPicture *picture = openTextPicture("Exe5Q4-B.txt");
    // printPicList(picture->pic);
    replicatePicture(*picture, 3, 2, "new rep.txt");

    freeTextPicture(picture);
    return 0;
}
