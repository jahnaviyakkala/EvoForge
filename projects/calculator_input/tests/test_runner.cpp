#include <cassert>
#include "CalculatorService.hpp"

int main() {
    CalculatorService calc;

    // Test addition
    assert(calc.add(2.0, 3.0) == 5.0);
    assert(calc.add(-1.0, -1.0) == -2.0);
    assert(calc.add(0.0, 0.0) == 0.0);

    // Test subtraction
    assert(calc.subtract(5.0, 3.0) == 2.0);
    assert(calc.subtract(-1.0, -1.0) == 0.0);
    assert(calc.subtract(0.0, 0.0) == 0.0);

    // Test multiplication
    assert(calc.multiply(2.0, 3.0) == 6.0);
    assert(calc.multiply(-1.0, -1.0) == 1.0);
    assert(calc.multiply(0.0, 0.0) == 0.0);

    // Test division
    assert(calc.divide(6.0, 2.0) == 3.0);
    assert(calc.divide(-4.0, -2.0) == 2.0);
    assert(calc.divide(0.0, 1.0) == 0.0);

    // Test division by zero
    try {
        calc.divide(1.0, 0.0);
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Division by zero error.");
    }

    return 0;
}
