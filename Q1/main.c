#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "NamesFile.h"

int main(int argc, char **argv)
{
    // Make sure we have all argc
    if (argc != 3)
        exit(MAIN_ARGS_ERROR);

    char *fileName = argv[1];
    int namesCount = atoi(argv[2]);
    // printf("%s, %d\n", fileName, namesCount);

    char** names = readBinaryNamesFile(fileName, namesCount);
    printf("Names loaded from file:\n");
    printNames(names, namesCount);

    removeCapitalLetters(names, namesCount);
    // printNames(names, namesCount);

    sortNames(names, namesCount);

    printf("Names sorted after removing capital letters:\n");
    printNames(names, namesCount);

    saveNamesFile(fileName, names, namesCount);
    freeNames(names, namesCount);

    return 0;
}

/////////////////////////////////////////////////////////////////////
