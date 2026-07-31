#include "calculator.hpp"

double calculator_add(double a, double b) { return a + b; }
double calculator_subtract(double a, double b) { return a - b; }
double calculator_multiply(double a, double b) { return a * b; }
bool calculator_divide(double a, double b, double &result) {
    if (b == 0.0) return false;
    result = a / b;
    return true;
}
