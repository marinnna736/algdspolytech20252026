#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "Header.h"

void Test_PerformOperation_Addition_Valid() {
    printf("Test 1: Сложение\n");
    long long result = PerformOperation(5, 3, '+');
    assert(result == 8);
    printf("Успех\n");
}

void Test_PerformOperation_Subtraction_Valid() {
    printf("Test 2: Вычитание\n");
    long long result = PerformOperation(10, 4, '-');
    assert(result == 6);
    printf("Успех\n");
}

void Test_PerformOperation_Multiplication_Valid() {
    printf("Test 3: Умножение\n");
    long long result = PerformOperation(7, 6, '*');
    assert(result == 42);
    printf("Успех\n");
}

void Test_PerformOperation_Division_Valid() {
    printf("Test 4: Деление\n");
    long long result = PerformOperation(20, 5, '/');
    assert(result == 4);
    printf("Успех\n");
}

void Test_PerformOperation_DivisionByZero_Zero() {
    printf("Test 5: Деление на ноль\n");
    long long result = PerformOperation(10, 0, '/');
    assert(result == 0);
    printf("Успех\n");
}

void Test_FindExpression_SimpleAddition_Valid() {
    printf("Test 6: Простое сложение\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression("123", 6, result);
    assert(found == true);
    assert(strcmp(result, "1+2+3") == 0);
    printf("Успех\n");
}

void Test_FindExpression_Multiplication_Valid() {
    printf("Test 7: Умножение\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression("23", 6, result);
    assert(found == true);
    assert(strcmp(result, "2*3") == 0);
    printf("Успех\n");
}

void Test_FindExpression_ComplexExample_Valid() {
    printf("Test 8: Сложный пример\n");
    char result[MAX_EXPR_LENGTH];
    long long target = 12 + 34 * 56 - 78 * 9;
    bool found = FindArithmeticExpression("123456789", target, result);
    assert(found == true);
    assert(strlen(result) > 0);
    printf("Успех\n");
}

void Test_FindExpression_NoSolution_False() {
    printf("Test 9: Нет решения\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression("111", 1000, result);
    assert(found == false);
    printf("Успех\n");
}

void Test_FindExpression_WithZeros_Valid() {
    printf("Test 10: С нулями\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression("1001", 2, result);
    assert(found == true);
    assert(strcmp(result, "1+0+0+1") == 0);
    printf("Успех\n");
}

void Test_FindExpression_EmptyString_False() {
    printf("Test 11: Пустая строка\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression("", 0, result);
    assert(found == false);
    printf("Успех\n");
}

void Test_FindExpression_NullInput_False() {
    printf("Test 12: NULL вход\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression(NULL, 0, result);
    assert(found == false);
    printf("Успех\n");
}

void Test_FindExpression_LargeNumber_Valid() {
    printf("Test 13: Большое число\n");
    char result[MAX_EXPR_LENGTH];
    char largeNumber[50];
    for (int i = 0; i < 49; i++) largeNumber[i] = '1';
    largeNumber[49] = '\0';

    bool found = FindArithmeticExpression(largeNumber, 49, result);
    assert(found == true);
    assert(strlen(result) > 0);
    printf("Успех\n");
}

void Test_FindExpression_NegativeTarget_Valid() {
    printf("Test 14: Отрицательная цель\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression("1234", -8, result);
    assert(found == true);
    assert(strlen(result) > 0);
    printf("Успех\n");
}

void Test_FindExpression_ZeroTarget_Valid() {
    printf("Test 15: Нулевая цель\n");
    char result[MAX_EXPR_LENGTH];
    bool found = FindArithmeticExpression("11", 0, result);
    assert(found == true);
    assert(strlen(result) > 0);
    printf("Успех\n");
}

int main() {
    printf("Запуск тестов...\n\n");
    
    Test_PerformOperation_Addition_Valid();
    Test_PerformOperation_Subtraction_Valid();
    Test_PerformOperation_Multiplication_Valid();
    Test_PerformOperation_Division_Valid();
    Test_PerformOperation_DivisionByZero_Zero();
    Test_FindExpression_SimpleAddition_Valid();
    Test_FindExpression_Multiplication_Valid();
    Test_FindExpression_ComplexExample_Valid();
    Test_FindExpression_NoSolution_False();
    Test_FindExpression_WithZeros_Valid();
    Test_FindExpression_EmptyString_False();
    Test_FindExpression_NullInput_False();
    Test_FindExpression_LargeNumber_Valid();
    Test_FindExpression_NegativeTarget_Valid();
    Test_FindExpression_ZeroTarget_Valid();
    
    printf("\nВсе 15 тестов успешно пройдены!\n");
    return 0;
}