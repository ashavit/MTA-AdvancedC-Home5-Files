All: FileFunctions.o PicFileManager.o
	gcc main.c FileFunctions.o PicFileManager.o PicListManager.c TextPictureManager.c -o main
	./main

FileFunctions.o: FileFunctions.c FileFunctions.h
	gcc -c FileFunctions.c


PicFileManager.o: PicFileManager.c PicFileManager.h PicListManager.h FileFunctions.h
	gcc -c PicFileManager.c

clear:
	rm main
	rm *.o
