#ifndef __STUDENTS_H__
#define __STUDENTS_H__

#include <stdio.h>

typedef struct _student
{
    char* name;	int average;} Student;

void sortStudentIndexesForFile(const char* fileName);
char ** findAverageGrade(char* database, int avgGrade, int * resSize);

#endif
