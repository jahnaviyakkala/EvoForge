#include <iostream>
#include "calculator.hpp"

int main() {
    std::cout << "=================================\n";
    std::cout << "     Interactive C++ Calculator  \n";
    std::cout << "=================================\n";
    std::cout << "1. Add (+)\n2. Subtract (-)\n3. Multiply (*)\n4. Divide (/)\n5. Exit\n";
    int choice;
    std::cout << "Select operation (1-5): ";
    if (!(std::cin >> choice) || choice == 5) {
        std::cout << "Exiting calculator.\n";
        return 0;
    }
    double a, b;
    std::cout << "Enter first number: ";
    if (!(std::cin >> a)) return 1;
    std::cout << "Enter second number: ";
    if (!(std::cin >> b)) return 1;
    if (choice == 1) {
        std::cout << "Result: " << a << " + " << b << " = " << calculator_add(a, b) << std::endl;
    } else if (choice == 2) {
        std::cout << "Result: " << a << " - " << b << " = " << calculator_subtract(a, b) << std::endl;
    } else if (choice == 3) {
        std::cout << "Result: " << a << " * " << b << " = " << calculator_multiply(a, b) << std::endl;
    } else if (choice == 4) {
        double res;
        if (calculator_divide(a, b, res)) {
            std::cout << "Result: " << a << " / " << b << " = " << res << std::endl;
        } else {
            std::cout << "Error: Division by zero!\n";
        }
    } else {
        std::cout << "Invalid choice.\n";
    }
    return 0;
}
