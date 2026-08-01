#ifndef CALCULATORSERVICE_HPP
#define CALCULATORSERVICE_HPP

class CalculatorService {
public:
    /**
     * Adds two numbers.
     *
     * @param a First number.
     * @param b Second number.
     * @return Sum of a and b.
     */
    double add(double a, double b);

    /**
     * Subtracts second number from first.
     *
     * @param a First number.
     * @param b Second number.
     * @return Difference between a and b.
     */
    double subtract(double a, double b);

    /**
     * Multiplies two numbers.
     *
     * @param a First number.
     * @param b Second number.
     * @return Product of a and b.
     */
    double multiply(double a, double b);

    /**
     * Divides first number by second.
     *
     * @param a First number.
     * @param b Second number.
     * @return Quotient of a divided by b.
     * @throws std::runtime_error if division by zero is attempted.
     */
    double divide(double a, double b);
};

#endif // CALCULATORSERVICE_HPP
