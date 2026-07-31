#include <cassert>
#include <iostream>
#include "calculator.hpp"

int main() {
    assert(calculator_add(2.0, 3.0) == 5.0);
    assert(calculator_subtract(5.0, 2.0) == 3.0);
    assert(calculator_multiply(4.0, 2.5) == 10.0);
    double res;
    assert(calculator_divide(10.0, 2.0, res) && res == 5.0);
    assert(!calculator_divide(5.0, 0.0, res));
    std::cout << "C++ Calculator tests passed." << std::endl;
    return 0;
}
