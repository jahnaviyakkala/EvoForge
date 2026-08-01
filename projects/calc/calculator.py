def add(a: float, b: float) -> float:
    """Add two numbers and return the result."""
    return a + b

def subtract(a: float, b: float) -> float:
    """Subtract the second number from the first and return the result."""
    return a - b

def multiply(a: float, b: float) -> float:
    """Multiply two numbers and return the result."""
    return a * b

def divide(a: float, b: float) -> float:
    """Divide the first number by the second and return the result.
    
    Raises:
        ValueError: If the divisor is zero.
    """
    if b == 0:
        raise ValueError("Division by zero is not allowed.")
    return a / b

def _parse_input(input_str: str) -> tuple:
    """Parse user input string into operation and operands."""
    parts = input_str.split()
    if len(parts) != 3:
        raise ValueError("Invalid input format. Please use 'operation operand1 operand2'.")
    
    operation, a_str, b_str = parts
    try:
        a = float(a_str)
        b = float(b_str)
    except ValueError:
        raise ValueError("Operands must be numeric.")
    
    return operation, a, b

def run() -> None:
    """Run the calculator CLI application."""
    print("Welcome to the Simple Calculator!")
    while True:
        user_input = input("Enter an operation (add, subtract, multiply, divide) and two numbers: ")
        if user_input.lower() == 'exit':
            print("Exiting the calculator. Goodbye!")
            break
        
        try:
            operation, a, b = _parse_input(user_input)
            if operation == 'add':
                result = add(a, b)
            elif operation == 'subtract':
                result = subtract(a, b)
            elif operation == 'multiply':
                result = multiply(a, b)
            elif operation == 'divide':
                result = divide(a, b)
            else:
                print("Invalid operation. Please choose from add, subtract, multiply, or divide.")
                continue
            
            print(f"The result is: {result:.2f}")
        
        except ValueError as e:
            print(f"Error: {e}")

if __name__ == "__main__":
    run()
