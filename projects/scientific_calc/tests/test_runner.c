#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "CalculatorService.h"
#include "ExpressionParser.h"

// Mock implementation of ExpressionParser for testing purposes
char** parse(const char* expression, int* size) {
    *size = 1;
    char** tokens = (char**)malloc(sizeof(char*) * (*size));
    tokens[0] = strdup(expression);
    return tokens;
}

int main() {
    // Test add function
    assert(add(2.0, 3.0) == 5.0);
    assert(add(-1.0, -1.0) == -2.0);
    assert(add(0.0, 0.0) == 0.0);

    // Test subtract function
    assert(subtract(5.0, 3.0) == 2.0);
    assert(subtract(-1.0, -1.0) == 0.0);
    assert(subtract(0.0, 0.0) == 0.0);

    // Test multiply function
    assert(multiply(2.0, 3.0) == 6.0);
    assert(multiply(-1.0, -1.0) == 1.0);
    assert(multiply(0.0, 5.0) == 0.0);

    // Test divide function
    assert(divide(6.0, 2.0) == 3.0);
    assert(divide(-4.0, -2.0) == 2.0);
    assert(divide(0.0, 5.0) == 0.0);

    // Test divide by zero
    printf("Testing division by zero...\n");
    int result = 1;
    try {
        double res = divide(5.0, 0.0);
        (void)res; // Avoid unused variable warning
    } catch (...) {
        result = 0;
    }
    assert(result == 0);

    printf("All tests passed!\n");
    return 0;
}
