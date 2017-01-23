#ifndef __EMPLOYEES_FILE_H__
#define __EMPLOYEES_FILE_H__

#include <stdio.h>

typedef struct _employee
{
      int    nameLength;
      char   *name;
      float  salary;
} Employee;

unsigned int loadBinaryEmployeesFile(const char* fileName, Employee ***array);
void saveBinaryEmployeesFile(const char *fileName, Employee **array, unsigned int size);

void raiseSalariesFromBinaryFile(const char* fileName, Employee **array, unsigned int size);
void sortEmployees(Employee **array, int size);

void printEmployees(Employee **array, unsigned int size);
void freeEmployeeArray(Employee** empArr, unsigned int size);

#endif
