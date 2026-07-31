#include "calcualtor_input.hpp"
#include <cmath>

double calcualtor_input_add(double a, double b) { return a + b; }
double calcualtor_input_subtract(double a, double b) { return a - b; }
double calcualtor_input_multiply(double a, double b) { return a * b; }
bool calcualtor_input_divide(double a, double b, double &result) {
    if (b == 0.0) return false;
    result = a / b;
    return true;
}
bool calcualtor_input_power(double base, double exponent, double &result) {
    result = std::pow(base, exponent);
    return !std::isnan(result);
}
bool calcualtor_input_sqrt(double val, double &result) {
    if (val < 0.0) return false;
    result = std::sqrt(val);
    return true;
}
bool calcualtor_input_log(double val, double &result) {
    if (val <= 0.0) return false;
    result = std::log(val);
    return true;
}
double calcualtor_input_sin(double rad) { return std::sin(rad); }
double calcualtor_input_cos(double rad) { return std::cos(rad); }
bool calcualtor_input_factorial(int n, double &result) {
    if (n < 0 || n > 170) return false;
    double res = 1.0;
    for (int i = 1; i <= n; ++i) res *= i;
    result = res;
    return true;
}
