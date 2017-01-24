#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include "Students.h"

void printNames(char **records,int size);
void freeRecords(char **records,int size);

/* Main provided for excercise */
int main(int argc, char **argv)
{
    char **records;
	int resSize;

	records = findAverageGrade(argv[1], 85, &resSize);
	printNames(records,resSize);

	freeRecords(records,resSize);

    return 0;
}

void printNames(char **records,int size)
{
	int i;
	printf("The students names are:\n");
	for (i=0 ; i<size ;i++ )
		printf("%s\n" , records[i]);
}

void freeRecords(char **records,int size)
{
	for (int i = 0; i < size; i++)
		free(records[i]);
    free(records);
}
