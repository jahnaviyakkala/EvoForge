#ifndef GENERATE_CALC_H
#define GENERATE_CALC_H

#include <stdbool.h>
#include <math.h>

double generate_calc_add(double a, double b);
double generate_calc_subtract(double a, double b);
double generate_calc_multiply(double a, double b);
bool generate_calc_divide(double a, double b, double *result);
bool generate_calc_power(double base, double exponent, double *result);
bool generate_calc_sqrt(double val, double *result);
bool generate_calc_factorial(int n, double *result);

#endif
