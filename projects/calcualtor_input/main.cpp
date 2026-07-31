#include <iostream>
#include "calcualtor_input.hpp"

int main() {
    std::cout << "=========================================\n";
    std::cout << "     Calcualtor Input CLI\n";
    std::cout << "=========================================\n";
    std::cout << "1. Add (+)\n2. Subtract (-)\n3. Multiply (*)\n4. Divide (/)\n"
                 "5. Power (a^b)\n6. Square Root (sqrt)\n7. Sin\n8. Cos\n9. Log (ln)\n10. Factorial (n!)\n0. Exit\n";
    int choice;
    while (std::cout << "\nSelect operation (0-10): " && (std::cin >> choice)) {
        if (choice == 0) {
            std::cout << "Exiting application.\n";
            break;
        }
        double a, b, res;
        if (choice >= 1 && choice <= 5) {
            std::cout << "Enter first number: "; if (!(std::cin >> a)) break;
            std::cout << "Enter second number: "; if (!(std::cin >> b)) break;
        } else if (choice >= 6 && choice <= 9) {
            std::cout << "Enter value: "; if (!(std::cin >> a)) break;
        }
        switch (choice) {
            case 1: std::cout << "Result: " << a << " + " << b << " = " << calcualtor_input_add(a, b) << "\n"; break;
            case 2: std::cout << "Result: " << a << " - " << b << " = " << calcualtor_input_subtract(a, b) << "\n"; break;
            case 3: std::cout << "Result: " << a << " * " << b << " = " << calcualtor_input_multiply(a, b) << "\n"; break;
            case 4:
                if (calcualtor_input_divide(a, b, res)) std::cout << "Result: " << a << " / " << b << " = " << res << "\n";
                else std::cout << "Error: Division by zero!\n"; break;
            case 5:
                if (calcualtor_input_power(a, b, res)) std::cout << "Result: " << a << " ^ " << b << " = " << res << "\n";
                else std::cout << "Error: Invalid power operation!\n"; break;
            case 6:
                if (calcualtor_input_sqrt(a, res)) std::cout << "Result: sqrt(" << a << ") = " << res << "\n";
                else std::cout << "Error: Cannot compute square root of negative number!\n"; break;
            case 7: std::cout << "Result: sin(" << a << ") = " << calcualtor_input_sin(a) << "\n"; break;
            case 8: std::cout << "Result: cos(" << a << ") = " << calcualtor_input_cos(a) << "\n"; break;
            case 9:
                if (calcualtor_input_log(a, res)) std::cout << "Result: ln(" << a << ") = " << res << "\n";
                else std::cout << "Error: Logarithm undefined for non-positive numbers!\n"; break;
            case 10: {
                int n;
                std::cout << "Enter integer n: ";
                if (std::cin >> n && calcualtor_input_factorial(n, res)) std::cout << "Result: " << n << "! = " << res << "\n";
                else std::cout << "Error: Invalid factorial input!\n"; break;
            }
            default: std::cout << "Invalid choice!\n"; break;
        }
    }
    return 0;
}
