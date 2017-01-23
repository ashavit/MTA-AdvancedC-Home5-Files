#include <stdlib.h>
#include <string.h>
#include "Constants.h"
#include "EmployeesFile.h"
#include "FileFunctions.h"

typedef struct _employeeListLoader
{
    Employee **array;
    unsigned int memSize, count;
} EmployeeListLoader;

static EmployeeListLoader createEmployeeLoader();
static void doubleEmployeesArraySize(Employee ***array, unsigned int *size);
static Employee** allocateEmployeesArray(unsigned int size);
void freeEmployeeArray(Employee** empArr, unsigned int size);
static Employee* allocateEmployee(unsigned int nameLength);
static void freeEmployee(Employee*);
static char* allocateString(unsigned int size);

static void merge(Employee **array, int left, int mid, int right);
static void mergeSort(Employee **array, int left, int right);

unsigned int loadBinaryEmployeesFile(const char* fileName, Employee ***array)
{
    FILE *input = openFile(fileName, "rb");

    EmployeeListLoader loader = createEmployeeLoader();

    // Find file data size
    fseek (input, 0 , SEEK_END);
    int ends = ftell(input) ;
    fseek (input, 0 , SEEK_SET);

    unsigned int length = 0;
    while(ftell(input) < ends)
    {
        binReadUnsignedInt(&length, 1, input);
        if (loader.count == loader.memSize)
            doubleEmployeesArraySize(&loader.array, &loader.memSize);

        loader.array[loader.count] = allocateEmployee(length);
        binReadString(((loader.array[loader.count])->name), length, input);
        binReadFloat(&((loader.array[loader.count])->salary), 1, input);

        loader.count++;
    }

    closeFile(input);

    *array = loader.array;
    return loader.count;
}

void saveBinaryEmployeesFile(const char *fileName, Employee **array, unsigned int size)
{
    FILE *save = openFile(fileName, "wb");

    for (int i = 0; i < size; ++i)
    {
        binWriteInt(array[i]->nameLength, save);
        binWriteString(array[i]->name, array[i]->nameLength, save);
        binWriteFloat(array[i]->salary, save);
    }

    closeFile(save);
}

void raiseSalariesFromBinaryFile(const char* fileName, Employee **array, unsigned int size)
{
    FILE *input = openFile(fileName, "rb");

    float raise;
    for (int i = 0; i < size; ++i)
    {
        raise = 0;
        binReadFloat(&raise, 1, input);
        array[i]->salary += raise;
    }

    closeFile(input);
}

void sortEmployees(Employee **array, int size)
{
    mergeSort(array, 0, size - 1);
}

void printEmployees(Employee **array, unsigned int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%s, %f\n", array[i]->name, array[i]->salary);
    }
    printf("\n");
}

void freeEmployeeArray(Employee** empArr, unsigned int size)
{
    if (empArr)
    {
        for (int i = 0; i < size; ++i)
            freeEmployee(empArr[i]);
        free(empArr);
    }
}

////////////////////////////////////

static EmployeeListLoader createEmployeeLoader()
{
    EmployeeListLoader loader;
    loader.count = loader.memSize = 0;
    loader.array = NULL;
    doubleEmployeesArraySize(&loader.array, &loader.memSize);
    return loader;
}

static void doubleEmployeesArraySize(Employee ***array, unsigned int *size)
{
    unsigned int newSize = (*size * 2) + 1;
    *array = (Employee**)realloc(*array, newSize * sizeof(Employee*));
    if (!array)
    {
        printf("Could not allocate Positions array");
        exit(MALLOC_ERROR);
    }
    *size = newSize;
}

static Employee** allocateEmployeesArray(unsigned int size)
{
    Employee **array = (Employee**)malloc(size * sizeof(Employee*));
    if (!array)
    {
        printf("Could not allocate Positions array");
        exit(MALLOC_ERROR);
    }
    return array;
}

static Employee* allocateEmployee(unsigned int nameLength)
{
    Employee *res = (Employee*)malloc(sizeof(Employee));
    if (!res)
    {
        printf("Error malloc");
        exit(MALLOC_ERROR);
    }
    res->nameLength = nameLength;
    res->name = allocateString(nameLength);
    res->salary = 0;
    return res;
}

static char* allocateString(unsigned int size)
{
    char *string = (char*)malloc(sizeof(char) * size);
    if (!string)
    {
        printf("Error malloc");
        exit(MALLOC_ERROR);
    }
    return string;
}

static void freeEmployee(Employee* emp)
{
    if (emp)
    {
        if (emp->name)
            free(emp->name);
        free(emp);
    }
}

static void merge(Employee **array, int left, int mid, int right)
{
    Employee **temp = allocateEmployeesArray(right - left + 1);

    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (array[i]->salary > array[j]->salary)
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    while (i <= mid)
        temp[k++] = array[i++];

    while (j <= right)
        temp[k++] = array[j++];

    while (k--, k >= 0)
        array[left + k] = temp[k];

    free(temp);
}

static void mergeSort(Employee **array, int left, int right)
{
    if (right <= left)
        return;

    int mid = (right - left) / 2;
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
}
