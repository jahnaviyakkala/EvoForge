import math

def add(a: float, b: float) -> float:
    return a + b

def subtract(a: float, b: float) -> float:
    return a - b

def multiply(a: float, b: float) -> float:
    return a * b

def divide(a: float, b: float) -> float:
    if b == 0:
        raise ValueError('Division by zero is not allowed.')
    return a / b

def power(base: float, exp: float) -> float:
    return math.pow(base, exp)

def square_root(val: float) -> float:
    if val < 0:
        raise ValueError('Cannot calculate square root of a negative number.')
    return math.sqrt(val)
