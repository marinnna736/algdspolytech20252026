#pragma warning (disable:4996)

#include <assert.h> 
#include <string.h>
#include "Header.h" 

void Test_StringToNumber_AlphaDigitString_ReturnNULLN1() {
    printf("Test 1: Numbers and letters or delimiters mixed in string\n");

    int len = 4;
    const char* str = ".f75";

    int res = StringToNumber(str, len);

    assert((res == -1));
    printf("Returned NULL. Error: letters or delimiters mixed in string\n");
}

void Test_StringToNumber_DigitString_ReturnNUMN2() {
    printf("Test 2: Just digits in string\n");

    int len = 3;
    const char* str = "137";

    int res = StringToNumber(str, len);

    assert((res == 137));
    printf("Success\n");
}

void Test_IsSameWorker_SameWorkers_ReturnTrueN3() {
    printf("Test 3: Same workers\n");

    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Алексей";    
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Алексей";     
    B.surname = "Морозов";   

    res = IsSameWorker(&A, &B);

    assert((res == 1));
    printf("Success\n");
}

void Test_IsSameWorker_DifferentWorkers_ReturnFalseN4() {
    printf("Test 4: Different workers\n");

    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";  

    res = IsSameWorker(&A, &B);

    assert((res == 0));
    printf("Success\n");
}

void Test_CompareWorkers_DifferentWorkers_ReturnTrueN5() {
    printf("Test 5: More hours\n");

    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Алексей";      /
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 4;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";  

    res = CompareWorkers(&A, &B);

    assert((res == 1));
    printf("Success\n");
}

void Test_CompareWorkers_DifferentWorkers_ReturnFalseN6() {
    printf("Test 6: Less Hours\n");

    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";   

    res = CompareWorkers(&A, &B);

    assert((res == 0));
    printf("Success\n");
}

void Test_CompareWorkers_DifferentWorkers_ReturnFalseN7() {
    printf("Test 7: Same Hours\n");

    Worker A;
    Worker B;
    int res;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 1;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";   

    res = CompareWorkers(&A, &B);

    assert((res == 0));
    printf("Success\n");
}

void Test_AddToSorted_PushForward_ValidValN8() {
    printf("Test 8: Push Forward\n");

    Worker A;
    Worker B;
    Worker C;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Алексей";     
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Дмитрий";     
    B.surname = "Ковалев";   

    C.day = 4;
    C.hours = 1;
    C.month = 2;
    C.name = "Федор";       
    C.surname = "Кузнецов";  

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;

    Head = AddToSorted(Head, Curr);

    assert((Head->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Head->NextWorker);
    free(Head);
}

void Test_AddToSorted_PushBack_ValidValN9() {
    printf("Test 9: Push Back\n");

    Worker A;
    Worker B;
    Worker C;

    A.day = 1;
    A.hours = 2;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";   

    C.day = 4;
    C.hours = 7;
    C.month = 2;
    C.name = "Федор";        
    C.surname = "Кузнецов";  

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;

    Head = AddToSorted(Head, Curr);

    assert((Head->NextWorker->NextWorker->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_AddToSorted_Insert_ValidValN10() {
    printf("Test 10: Insert\n");

    Worker A;
    Worker B;
    Worker C;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";   

    C.day = 4;
    C.hours = 2;
    C.month = 2;
    C.name = "Федор";       
    C.surname = "Кузнецов";  

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;

    Head = AddToSorted(Head, Curr);

    assert((Head->NextWorker->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_SortStaffList_NULLStaff_ReturnNULLN11() {
    printf("Test 11: NULL Staff\n");

    Staff* Head = NULL;

    Head = SortStaffList(Head);

    assert((Head == NULL));
    printf("Returned NULL. Error: NULL Staff\n");
}

void Test_SortStaffList_SortedStaff_ValidValN12() {
    printf("Test 12: Sorted Staff\n");

    Worker A;
    Worker B;
    Worker C;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 2;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";  

    C.day = 4;
    C.hours = 3;
    C.month = 2;
    C.name = "Федор";       
    C.surname = "Кузнецов";  

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    Head = SortStaffList(Head);

    assert((Head->CurrWorker == &A) && (Head->NextWorker->CurrWorker == &B) && (Head->NextWorker->NextWorker->CurrWorker == &C));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_SortStaffList_RandStaff_ValidValN13() {
    printf("Test 13: Random Staff\n");

    Worker A;
    Worker B;
    Worker C;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 3;
    B.month = 2;
    B.name = "Дмитрий";     
    B.surname = "Ковалев";   

    C.day = 4;
    C.hours = 2;
    C.month = 2;
    C.name = "Федор";       
    C.surname = "Кузнецов";  

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    Head = SortStaffList(Head);

    assert((Head->CurrWorker == &A) && (Head->NextWorker->CurrWorker == &C) && (Head->NextWorker->NextWorker->CurrWorker == &B));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_ParseWorker_NULLLines_ReturnNULLN14() {
    printf("Test 14: NULL Lines\n");

    char* lines = NULL;
    Worker* res;
    int pos = 1;

    res = ParseWorker(lines, 6, &pos);
    assert(res == NULL);
    printf("Returned NULL. Error: NULL Lines\n");
}

void Test_ParseWorker_NULLLen_ReturnNULLN15() {
    printf("Test 15: NULL Length\n");

    char* lines = "15.01.2024 Морозов Алексей 7";  
    Worker* res;
    int pos = 1;

    res = ParseWorker(lines, 0, &pos);
    assert(res == NULL);
    printf("Returned NULL. Error: NULL length\n");
}

void Test_ParseWorker_RandWorker_ValidValN16() {
    printf("Test 16: Parse Worker\n");

    const char* lines = "15.01.2024 Морозов Алексей 7\n";  
    int pos = 0;
    int len = 25;  

    Worker expected;
    expected.day = 15;
    expected.hours = 7;
    expected.month = 1;
    expected.name = "Алексей";    
    expected.surname = "Морозов"; 
    expected.year = 2024;

    Worker* res;
    res = ParseWorker(lines, len, &pos);

    assert((expected.day == res->day) &&
        (expected.month == res->month) &&
        (expected.year == res->year) &&
        (expected.hours == res->hours) &&
        (strcmp(expected.name, res->name) == 0) &&
        (strcmp(expected.surname, res->surname) == 0));

    printf("Success\n");
    free(res->name);
    free(res->surname);
    free(res);
}

void Test_BuildStaffList_NULLLines_ReturnNULLN17() {
    printf("Test 17: NULL Lines\n");

    char* lines = NULL;
    int len = 25;
    Staff* res;

    res = BuildStaffList(lines, len);
    assert(res == NULL);
    printf("Returned NULL. Error: NULL Lines\n");
}

void Test_BuildStaffList_RandStaff_ValidValN18() {
    printf("Test 18: Random Staff\n");

    char* lines = "15.01.2024 Морозов Алексей 7\n03.01.2024 Ковалев Дмитрий 7";  
    int len = 70;  
    Staff* res;

    Worker A;
    Worker B;
    A.day = 15; B.day = 3;
    A.month = 1; B.month = 1;
    A.year = 2024; B.year = 2024;
    A.name = "Алексей"; B.name = "Дмитрий";      
    A.surname = "Морозов"; B.surname = "Ковалев"; 
    A.hours = 7; B.hours = 7;

    res = BuildStaffList(lines, len);

    assert((strcmp(res->CurrWorker->surname, A.surname) == 0) &&
        (strcmp(res->NextWorker->CurrWorker->surname, B.surname) == 0));

    printf("Success\n");
    CleanupStaff(res);
}

void Test_ExtractData_NULLLines_ReturnNULLN19() {
    printf("Test 19: NULL Lines\n");

    char* lines = "NULL";
    int pos = 0;
    int dataLen = 0;

    char* res = ExtractData(lines, 0, &pos, &dataLen, ' ');
    assert(res == NULL);
    printf("Returned NULL. Error: NULL Lines\n");
}

void Test_ExtractData_NoEndChar_ReturnNULLN20() {
    printf("Test 20: No End Character\n");

    char* lines = "15.01.2024 Морозов Алексей 7\n03.01.2024 Ковалев Дмитрий 7";  
    int pos = 0;
    int dataLen = 0;

    char* res = ExtractData(lines, 0, &pos, &dataLen, '/');
    assert(res == NULL);
    printf("Returned NULL. Error: There is no EndChar in lines\n");
}

void Test_ExtractData_ReadData_ValidValN21() {
    printf("Test 21: Read Data\n");

    char* lines = "15.01.2024 Морозов Алексей 7\n03.01.2024 Ковалев Дмитрий 7";  
    int pos = 0;
    int dataLen = 0;

    char* res = ExtractData(lines, 70, &pos, &dataLen, '.');  
    assert(strcmp(res, "15") == 0);
    printf("Success\n");
    free(res);
}

void Test_FindAndPrint_NoOnePrinted_ReturnFalseN22() {
    printf("Test 22: No One Printed\n");

    Worker A;
    Worker B;
    Worker C;

    A.day = 1;
    A.hours = 1;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.hours = 2;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";   

    C.day = 4;
    C.hours = 3;
    C.month = 2;
    C.name = "Федор";        
    C.surname = "Кузнецов";  

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    int res = FindAndPrint(Head, 7);

    assert((res == 0));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

void Test_FindAndPrint_NULLStaff_ReturnFalseN23() {
    printf("Test 23: NULL Staff\n");

    Staff* Head = NULL;
    int res;

    res = FindAndPrint(Head, 7);

    assert((res == 0));
    printf("Success\n");
}

void Test_FindAndPrint_WorkersPrinted_ReturnTrueN24() {
    printf("Test 24: Workers Printed\n");

    Worker A;
    Worker B;
    Worker C;

    A.day = 1;
    A.year = 2024;
    A.hours = 1;
    A.month = 5;
    A.name = "Алексей";      
    A.surname = "Морозов";   

    B.day = 4;
    B.year = 2024;
    B.hours = 2;
    B.month = 2;
    B.name = "Дмитрий";      
    B.surname = "Ковалев";   

    C.day = 4;
    C.year = 2024;
    C.hours = 3;
    C.month = 2;
    C.name = "Федор";        
    C.surname = "Кузнецов";  

    Staff* Head = (Staff*)malloc(sizeof(Staff));
    Staff* Curr = (Staff*)malloc(sizeof(Staff));
    Staff* Tail = (Staff*)malloc(sizeof(Staff));

    Curr->CurrWorker = &C;
    Curr->NextWorker = NULL;

    Tail->CurrWorker = &B;
    Tail->NextWorker = NULL;

    Head->CurrWorker = &A;
    Head->NextWorker = Tail;
    Head->NextWorker->NextWorker = Curr;

    int res = FindAndPrint(Head, 1);

    assert((res == 1));
    printf("Success\n");
    free(Tail);
    free(Curr);
    free(Head);
}

int main(void) {
    setlocale(LC_CTYPE, "Russian");
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

    Test_StringToNumber_AlphaDigitString_ReturnNULLN1();
    Test_StringToNumber_DigitString_ReturnNUMN2();
    Test_IsSameWorker_SameWorkers_ReturnTrueN3();
    Test_IsSameWorker_DifferentWorkers_ReturnFalseN4();
    Test_CompareWorkers_DifferentWorkers_ReturnTrueN5();
    Test_CompareWorkers_DifferentWorkers_ReturnFalseN6();
    Test_CompareWorkers_DifferentWorkers_ReturnFalseN7();
    Test_AddToSorted_PushForward_ValidValN8();
    Test_AddToSorted_PushBack_ValidValN9();
    Test_AddToSorted_Insert_ValidValN10();
    Test_SortStaffList_NULLStaff_ReturnNULLN11();
    Test_SortStaffList_SortedStaff_ValidValN12();
    Test_SortStaffList_RandStaff_ValidValN13();
    Test_ParseWorker_NULLLines_ReturnNULLN14();
    Test_ParseWorker_NULLLen_ReturnNULLN15();
    Test_ParseWorker_RandWorker_ValidValN16();
    Test_BuildStaffList_NULLLines_ReturnNULLN17();
    Test_BuildStaffList_RandStaff_ValidValN18();
    Test_ExtractData_NULLLines_ReturnNULLN19();
    Test_ExtractData_NoEndChar_ReturnNULLN20();
    Test_ExtractData_ReadData_ValidValN21();
    Test_FindAndPrint_NoOnePrinted_ReturnFalseN22();
    Test_FindAndPrint_NULLStaff_ReturnFalseN23();
    Test_FindAndPrint_WorkersPrinted_ReturnTrueN24();

    return 0;
}