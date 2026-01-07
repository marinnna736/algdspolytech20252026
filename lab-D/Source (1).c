#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool FindArithmeticExpression(const char* numberString, long long targetValue, char* outputExpression) {
    outputExpression[0] = '\0';

    if (numberString == NULL || numberString[0] == '\0') {
        return false;
    }

    return ExpressionGenerator(numberString, 0, 0, 0, "", targetValue, outputExpression);
}

bool ExpressionGenerator(const char* digits, int currentPosition, long long currentTotal,
    long long previousValue, const char* currentExpression, long long target,
    char* resultBuffer) {
    
    int digitCount = strlen(digits);

    if (currentPosition == digitCount) {
        if (currentTotal == target) {
            strcpy(resultBuffer, currentExpression);
            return true;
        }
        return false;
    }

    long long currentNumber = 0;
    char newExpression[MAX_EXPR_LENGTH];
    char numberString[MAX_NUM_DIGITS];

    for (int i = currentPosition; i < digitCount; i++) {
        currentNumber = currentNumber * 10 + (digits[i] - '0');

        int numberLength = i - currentPosition + 1;
        strncpy(numberString, digits + currentPosition, numberLength);
        numberString[numberLength] = '\0';

        if (currentPosition == 0) {
            snprintf(newExpression, sizeof(newExpression), "%s", numberString);
            if (ExpressionGenerator(digits, i + 1, currentNumber, currentNumber, 
                newExpression, target, resultBuffer)) {
                return true;
            }
        }
        else {
            char operators[] = "+-*/";
            for (int opIndex = 0; opIndex < 4; opIndex++) {
                snprintf(newExpression, sizeof(newExpression), "%s%c%s", 
                         currentExpression, operators[opIndex], numberString);

                long long updatedTotal = 0;
                long long updatedPrevious = 0;

                switch (operators[opIndex]) {
                case '+':
                    updatedTotal = currentTotal + currentNumber;
                    updatedPrevious = currentNumber;
                    break;
                case '-':
                    updatedTotal = currentTotal - currentNumber;
                    updatedPrevious = -currentNumber;
                    break;
                case '*':
                    updatedTotal = currentTotal - previousValue + previousValue * currentNumber;
                    updatedPrevious = previousValue * currentNumber;
                    break;
                case '/':
                    if (currentNumber == 0) continue;
                    if (previousValue % currentNumber != 0) continue;
                    updatedTotal = currentTotal - previousValue + previousValue / currentNumber;
                    updatedPrevious = previousValue / currentNumber;
                    break;
                }

                if (ExpressionGenerator(digits, i + 1, updatedTotal, updatedPrevious, 
                    newExpression, target, resultBuffer)) {
                    return true;
                }
            }
        }

        if (digits[currentPosition] == '0') {
            break;
        }
    }

    return false;
}

long long PerformOperation(long long operandA, long long operandB, char operation) {
    switch (operation) {
    case '+': return operandA + operandB;
    case '-': return operandA - operandB;
    case '*': return operandA * operandB;
    case '/':
        if (operandB == 0) return 0;
        return operandA / operandB;
    default: return 0;
    }
}

/*
int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile) {
        return 1;
    }

    char inputDigits[101];
    long long requiredResult;

    if (fscanf(inputFile, "%s %lld", inputDigits, &requiredResult) != 2) {
        fclose(inputFile);
        fclose(outputFile);
        return 1;
    }

    char finalExpression[MAX_EXPR_LENGTH];

    if (FindArithmeticExpression(inputDigits, requiredResult, finalExpression)) {
        fprintf(outputFile, "%s\n", finalExpression);
        printf("Найдено выражение: %s\n", finalExpression);
    }
    else {
        fprintf(outputFile, "0\n");
        printf("Выражение не найдено\n");
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
*/