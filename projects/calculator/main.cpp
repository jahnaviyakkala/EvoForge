#include <iostream>
#include "calculator.hpp"

int main() {
    std::cout << "=== Interactive C++ Calculator ===" << std::endl;
    std::cout << "Available operations: +, -, *, / (or enter 'q' to quit)" << std::endl;

    char op;
    double a, b, res;

    while (true) {
        std::cout << "\nEnter operation (+, -, *, /) or 'q': ";
        if (!(std::cin >> op) || op == 'q' || op == 'Q') {
            std::cout << "Exiting calculator." << std::endl;
            break;
        }

        std::cout << "Enter two numbers: ";
        if (!(std::cin >> a >> b)) {
            std::cout << "Invalid number input. Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (op) {
            case '+':
                std::cout << "Result: " << a << " + " << b << " = " << calculator_add(a, b) << std::endl;
                break;
            case '-':
                std::cout << "Result: " << a << " - " << b << " = " << calculator_subtract(a, b) << std::endl;
                break;
            case '*':
                std::cout << "Result: " << a << " * " << b << " = " << calculator_multiply(a, b) << std::endl;
                break;
            case '/':
                if (calculator_divide(a, b, res)) {
                    std::cout << "Result: " << a << " / " << b << " = " << res << std::endl;
                } else {
                    std::cout << "Error: Division by zero is not allowed." << std::endl;
                }
                break;
            default:
                std::cout << "Unknown operation '" << op << "'. Use +, -, *, or /." << std::endl;
                break;
        }
    }
    return 0;
}
