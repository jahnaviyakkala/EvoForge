from calculation_service import CalculationService

class CalculatorCLI:
    def __init__(self):
        self.calculation_service = CalculationService()

    def run(self):
        while True:
            try:
                expression = input("Enter operation (add, subtract, multiply, divide) and two operands separated by spaces: ")
                parts = expression.split()
                
                if len(parts) != 3:
                    print("Invalid input. Please enter the operation and two operands.")
                    continue
                
                operation, operand1, operand2 = parts
                operand1 = float(operand1)
                operand2 = float(operand2)

                result = self.handle_operation(operation, operand1, operand2)
                print(f"Result: {result}")

            except ValueError as ve:
                print(f"Error: {ve}")
            except Exception as e:
                print(f"An unexpected error occurred: {e}")

    def handle_operation(self, operation: str, a: float, b: float) -> float:
        if operation == "add":
            return self.calculation_service.add(a, b)
        elif operation == "subtract":
            return self.calculation_service.subtract(a, b)
        elif operation == "multiply":
            return self.calculation_service.multiply(a, b)
        elif operation == "divide":
            return self.calculation_service.divide(a, b)
        else:
            raise ValueError("Invalid operation. Supported operations are add, subtract, multiply, and divide.")

if __name__ == "__main__":
    calculator = CalculatorCLI()
    calculator.run()
