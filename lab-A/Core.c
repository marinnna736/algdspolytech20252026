#pragma warning (disable:4996)

#include "Header.h" 

#define _CRTDBG_MAP_ALLOC 

void DisplayWorker(Worker* worker) {  
    printf("%02d.%02d.%04d %s %s %lf\n", worker->day, worker->month, worker->year, worker->surname, worker->name, worker->hours);
}

int FindAndPrint(Staff* head, double limit) {  
    int printed = 0;  
    Staff* curr = head;  
    Staff* tmp;  
    double sum = 0;  

    while (curr != NULL) {
        tmp = head;
        sum = curr->CurrWorker->hours;

        while (tmp != NULL) {
            if (IsSameWorker(tmp->CurrWorker, curr->CurrWorker) && (tmp != curr)) {
                sum += tmp->CurrWorker->hours;
            }
            tmp = tmp->NextWorker;
        }

        if (sum > limit) {
            printed = 1;
            printf("%s %s %02d.%02d.%04d \n",
                curr->CurrWorker->surname,
                curr->CurrWorker->name,
                curr->CurrWorker->day,
                curr->CurrWorker->month,
                curr->CurrWorker->year);
        }
        curr = curr->NextWorker;
    }
    return printed;
}

int IsSameWorker(Worker* w1, Worker* w2) {  
    if ((strcmp(w1->surname, w2->surname) == 0) && (strcmp(w1->name, w2->name) == 0)) {
        return 1;
    }
    return 0;
}

int CompareWorkers(Worker* w1, Worker* w2) {  
    if (w1->hours < w2->hours) {
        return 1;
    }
    else if (w1->hours == w2->hours) {
        if (strcmp(w1->surname, w2->surname) < 0) {
            return 1;
        }
        else if (strcmp(w1->surname, w2->surname) == 0) {
            if ((strcmp(w1->name, w2->name) < 0)) {
                return 1;
            }
            else if (strcmp(w1->name, w2->name) == 0) {
                if (w1->year < w2->year) {
                    return 1;
                }
                else if (w1->year == w2->year) {
                    if (w1->month < w2->month) {
                        return 1;
                    }
                    else if (w1->month == w2->month) {
                        if (w1->day < w2->day) {
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

char* ReadTextFile(const char* filename, int* size) {  
    FILE* file = fopen(filename, "r");  
    char* buffer = (char*)malloc(sizeof(char));  
    char ch;  
    int i = 0;

    while (fscanf(file, "%c", &ch) != EOF) {
        buffer = (char*)realloc(buffer, (i + 1) * sizeof(char));
        *(buffer + i) = ch;
        i++;
    }
    *size = i;  

    fclose(file);
    return buffer;
}

int StringToNumber(char* str, int len) {  
    int result = 0;  
    for (int i = 0; i < len; i++) {
        result *= 10;
        if ((str[i] < 48) || (str[i] > 57)) {
            return -1;
        }
        result += ((int)str[i] - 48);
    }
    return result;
}

char* ExtractData(char* source, int size, int* pos, int* dataLen, char delimiter) {  // ашкн: ReadOneData
    if (source == NULL || pos == NULL || dataLen == NULL || size <= 0 || *pos < 0) {
        return NULL;
    }

    char* data;
    *dataLen = 0;  
    data = (char*)malloc(sizeof(char));  
    if (data == NULL) { return 0; }

    while (source[*pos] != delimiter) {
        if (source[*pos] == "\n") {
            return NULL;
        }
        (*dataLen)++;
        data = (char*)realloc(data, (*dataLen) * sizeof(char));
        if (data == NULL) {
            return 0;
        }
        data[(*dataLen) - 1] = source[*pos];
        (*pos)++;
        if ((*pos) == size) {
            break;
        }
    }

    data = (char*)realloc(data, (*dataLen + 1) * sizeof(char));
    data[(*dataLen)] = '\0';
    return data;
}

Worker* ParseWorker(char* source, int size, int* pos) {  
    Worker* newWorker; 
    int* lenPtr;
    char* data;  
    int dataLen = 0;  
    lenPtr = &dataLen;

    newWorker = (Worker*)malloc(sizeof(Worker));
    if (newWorker == NULL) { return 0; }
    if ((source == NULL) || (size == 0)) {
        free(newWorker);
        return NULL;
    }

    data = ExtractData(source, size, pos, lenPtr, '.');
    newWorker->day = StringToNumber(data, dataLen);
    (*pos)++;
    *lenPtr = 0;
    free(data);

    data = ExtractData(source, size, pos, lenPtr, '.');
    newWorker->month = StringToNumber(data, dataLen);
    (*pos)++;
    *lenPtr = 0;
    free(data);

    data = ExtractData(source, size, pos, lenPtr, ' ');
    newWorker->year = (int)StringToNumber(data, dataLen);
    (*pos)++;
    *lenPtr = 0;
    free(data);

    data = ExtractData(source, size, pos, lenPtr, ' ');
    newWorker->surname = data;
    (*pos)++;
    *lenPtr = 0;

    data = ExtractData(source, size, pos, lenPtr, ' ');
    newWorker->name = data;
    (*pos)++;
    *lenPtr = 0;

    data = ExtractData(source, size, pos, lenPtr, '\n');
    newWorker->hours = (double)StringToNumber(data, dataLen);
    *lenPtr = 0;
    free(data);

    return newWorker;
}

Staff* BuildStaffList(char* source, int size) {  
    Staff* head = NULL;
    Staff* tail = NULL;
    Staff* node = NULL;  
    Worker* worker;  
    int i = 0;

    if (source == NULL) {
        return NULL;
    }

    while (i < size) {
        worker = ParseWorker(source, size, &i);
        i++;
        if (worker == NULL) { return NULL; }

        node = (Staff*)malloc(sizeof(Staff));
        node->CurrWorker = worker;
        node->NextWorker = NULL;

        if (head == NULL) {
            head = node;
            tail = node;
        }
        else {
            tail->NextWorker = node;
            tail = node;
        }
    }
    return head;
}

void CleanupStaff(Staff* head) {  
    Staff* current = head;
    Staff* next;

    while (current != NULL) {
        next = current->NextWorker;
        if (current->CurrWorker != NULL) {
            if (current->CurrWorker->name != NULL)
                free((void*)current->CurrWorker->name);
            if (current->CurrWorker->surname != NULL)
                free((void*)current->CurrWorker->surname);
            free(current->CurrWorker);
        }
        free(current);
        current = next;
    }
}

Staff* AddToSorted(Staff* sorted, Staff* node) {  
    Staff* current = sorted;  

    if ((sorted == NULL) || CompareWorkers(node->CurrWorker, sorted->CurrWorker)) {
        node->NextWorker = sorted;
        return node;
    }

    current = sorted;
    while ((current->NextWorker != NULL) && CompareWorkers(current->NextWorker->CurrWorker, node->CurrWorker)) {
        current = current->NextWorker;
    }

    node->NextWorker = current->NextWorker;
    current->NextWorker = node;
    return sorted;
}

Staff* SortStaffList(Staff* Head) {  
    Staff* sorted = NULL;
    Staff* current = Head;  
    Staff* nextNode;  

    while (current != NULL) {
        nextNode = current->NextWorker;
        sorted = AddToSorted(sorted, current);
        current = nextNode;
    }
    return sorted;
}

/*int main() {
    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    const char* inputFile = "StaffFile.txt";  // ашкн: StaffFile
    int size = 0;  
    double limit;  
    char* content; 
    Staff* staffList;  

    content = ReadTextFile(inputFile, &size);
    scanf("%lf", &limit);

    staffList = BuildStaffList(content, size);
    staffList = SortStaffList(staffList);
    FindAndPrint(staffList, limit);

    CleanupStaff(staffList);
    free(content);
}*/