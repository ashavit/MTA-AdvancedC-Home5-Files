#include <stdio.h>
#include <stdlib.h>
#include "Models.h"
#include "TextPictureManager.h"
#include "PicListManager.h"
#include "PicFileManager.h"

int main(int argc, char **argv)
{
    TextPicture picture = createTestTextPicture();
    paintTextPicture(picture, "my pic.txt");
    clearTestTextPicture(picture);

    return 0;
}
