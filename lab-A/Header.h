#pragma once

#include <stdio.h>
#include <math.h> 
#include <locale.h> 
#include <malloc.h> 
#include <stdlib.h> 
#include <crtdbg.h> 

typedef struct {
    int day;
    int month;
    int year;
    char* surname;
    char* name;
    double hours;
} Worker;

typedef struct Staff {
    Worker* CurrWorker;
    struct Staff* NextWorker;
} Staff;

void CleanupStaff(Staff* head);  
void DisplayWorker(Worker* worker); 
int FindAndPrint(Staff* head, double limit);  
int IsSameWorker(Worker* w1, Worker* w2);  
int CompareWorkers(Worker* w1, Worker* w2);  
int StringToNumber(char* str, int len);  
char* ExtractData(char* lines, int size, int* pos, int* dataLen, char delimiter);  
Worker* ParseWorker(char* source, int size, int* pos);  
Staff* BuildStaffList(char* source, int size);  
Staff* AddToSorted(Staff* sorted, Staff* node); 
Staff* SortStaffList(Staff* Head);  
