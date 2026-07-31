#ifndef CALCUALTOR_INPUT_HPP
#define CALCUALTOR_INPUT_HPP

#include <cmath>

double calcualtor_input_add(double a, double b);
double calcualtor_input_subtract(double a, double b);
double calcualtor_input_multiply(double a, double b);
bool calcualtor_input_divide(double a, double b, double &result);
bool calcualtor_input_power(double base, double exponent, double &result);
bool calcualtor_input_sqrt(double val, double &result);
bool calcualtor_input_log(double val, double &result);
double calcualtor_input_sin(double rad);
double calcualtor_input_cos(double rad);
bool calcualtor_input_factorial(int n, double &result);

#endif
