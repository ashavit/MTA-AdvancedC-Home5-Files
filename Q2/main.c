#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "EmployeesFile.h"

int main(int argc, char **argv)
{
    // Make sure we have all argc
    if (argc != 3)
        exit(MAIN_ARGS_ERROR);

    char *empFileName = argv[1];
    char *raiseFileName = argv[2];
    // printf("%s, %s\n", empFileName, raiseFileName);

    Employee **empsArray;
    unsigned int empCount = loadBinaryEmployeesFile(empFileName, &empsArray);

    printf("Employees loaded from file:\n");
    printEmployees(empsArray, empCount);

    raiseSalariesFromBinaryFile(raiseFileName, empsArray, empCount);
    // printEmployees(empsArray, empCount);

    sortEmployees(empsArray, empCount);
    printf("Employees after raise and sort:\n");
    printEmployees(empsArray, empCount);

    saveBinaryEmployeesFile(empFileName, empsArray, empCount);
    freeEmployeeArray(empsArray, empCount);
    
    return 0;
}

/////////////////////////////////////////////////////////////////////
