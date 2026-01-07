#pragma once
#include <stdbool.h>

#define MAX_NUM_DIGITS 100
#define MAX_EXPR_LENGTH 300

bool FindArithmeticExpression(const char* numberString, long long targetValue, char* outputExpression);
bool ExpressionGenerator(const char* digits, int currentPosition, long long currentTotal,
    long long previousValue, const char* currentExpression,
    long long target, char* resultBuffer);
long long PerformOperation(long long operandA, long long operandB, char operation);