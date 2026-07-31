#ifndef SCIENTIFC_CALC_H
#define SCIENTIFC_CALC_H

#include <stdbool.h>
#include <math.h>

double scientifc_calc_add(double a, double b);
double scientifc_calc_subtract(double a, double b);
double scientifc_calc_multiply(double a, double b);
bool scientifc_calc_divide(double a, double b, double *result);
bool scientifc_calc_power(double base, double exponent, double *result);
bool scientifc_calc_sqrt(double val, double *result);
bool scientifc_calc_factorial(int n, double *result);

#endif
