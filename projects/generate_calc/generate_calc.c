#include "generate_calc.h"
#include <math.h>

double generate_calc_add(double a, double b) { return a + b; }
double generate_calc_subtract(double a, double b) { return a - b; }
double generate_calc_multiply(double a, double b) { return a * b; }
bool generate_calc_divide(double a, double b, double *result) {
    if (b == 0.0) return false;
    if (result) *result = a / b;
    return true;
}
bool generate_calc_power(double base, double exponent, double *result) {
    double res = pow(base, exponent);
    if (isnan(res)) return false;
    if (result) *result = res;
    return true;
}
bool generate_calc_sqrt(double val, double *result) {
    if (val < 0.0) return false;
    if (result) *result = sqrt(val);
    return true;
}
bool generate_calc_factorial(int n, double *result) {
    if (n < 0 || n > 170) return false;
    double res = 1.0;
    for (int i = 1; i <= n; ++i) res *= i;
    if (result) *result = res;
    return true;
}
