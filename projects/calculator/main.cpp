#include <iostream>
#include "calculator.hpp"

int main() {
    std::cout << "2 + 3 = " << calculator_add(2, 3) << std::endl;
    double res;
    if (calculator_divide(10, 2, res)) std::cout << "10 / 2 = " << res << std::endl;
    return 0;
}
