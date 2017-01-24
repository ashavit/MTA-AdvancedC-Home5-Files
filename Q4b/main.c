#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Students.h"

int main(int argc, char **argv)
{
    // Make sure we have all argc
    if (argc != 2)
        exit(MAIN_ARGS_ERROR);

    char *dbFileName = argv[1];
    // printf("%s\n", dbFileName);

    sortStudentIndexesForFile(dbFileName);

    return 0;
}
