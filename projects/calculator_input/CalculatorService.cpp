#include "CalculatorService.hpp"
#include <stdexcept>

double CalculatorService::add(double a, double b) {
    return a + b;
}

double CalculatorService::subtract(double a, double b) {
    return a - b;
}

double CalculatorService::multiply(double a, double b) {
    return a * b;
}

double CalculatorService::divide(double a, double b) {
    if (b == 0.0) {
        throw std::runtime_error("Division by zero error.");
    }
    return a / b;
}
