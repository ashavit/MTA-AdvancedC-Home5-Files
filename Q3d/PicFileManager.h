#ifndef __PIC_FILE_MANAGER_H__
#define __PIC_FILE_MANAGER_H__

#include <stdio.h>
#include "Models.h"

void paintTextPicture(TextPicture textPic, char* filename);
TextPicture * openTextPicture(char* filename);

void replicatePicture(TextPicture srcPic, int m, int n, char* repPicFileName);
void mergePictures(TextPicture* bigPic, char* smallPic);

#endif
