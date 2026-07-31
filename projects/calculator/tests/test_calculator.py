import pytest
from calculator import add, subtract, multiply, divide, power, square_root

def test_calculator_basic():
    assert add(2, 3) == 5
    assert subtract(10, 4) == 6
    assert multiply(3, 4) == 12
    assert divide(10, 2) == 5.0
    assert power(2, 3) == 8.0
    assert square_root(25) == 5.0

def test_calculator_divide_by_zero():
    with pytest.raises(ValueError):
        divide(5, 0)

def test_calculator_negative_sqrt():
    with pytest.raises(ValueError):
        square_root(-4)
