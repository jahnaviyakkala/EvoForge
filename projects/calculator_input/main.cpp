#include <iostream>
#include <string>
#include <sstream>
#include "CalculatorService.hpp"

int main() {
    CalculatorService calc;
    std::string input;
    
    while (true) {
        std::cout << "Enter operation (add, subtract, multiply, divide) and two operands: ";
        std::getline(std::cin, input);
        
        if (input.empty()) {
            continue;
        }
        
        std::istringstream iss(input);
        std::string operation;
        double operand1, operand2;
        
        if (!(iss >> operation >> operand1 >> operand2)) {
            std::cerr << "Invalid input format. Please enter: operation operand1 operand2" << std::endl;
            continue;
        }
        
        try {
            double result = 0.0;
            if (operation == "add") {
                result = calc.add(operand1, operand2);
            } else if (operation == "subtract") {
                result = calc.subtract(operand1, operand2);
            } else if (operation == "multiply") {
                result = calc.multiply(operand1, operand2);
            } else if (operation == "divide") {
                result = calc.divide(operand1, operand2);
            } else {
                std::cerr << "Invalid operation. Please choose from add, subtract, multiply, divide." << std::endl;
                continue;
            }
            
            std::cout << "Result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    return 0;
}
