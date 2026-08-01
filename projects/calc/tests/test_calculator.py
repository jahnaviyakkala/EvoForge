import pytest
from calculator import add, subtract, multiply, divide, _parse_input

def test_add():
    assert add(1.0, 2.0) == 3.0
    assert add(-1.0, -1.0) == -2.0
    assert add(0.0, 0.0) == 0.0

def test_subtract():
    assert subtract(5.0, 3.0) == 2.0
    assert subtract(-1.0, -1.0) == 0.0
    assert subtract(0.0, 0.0) == 0.0

def test_multiply():
    assert multiply(4.0, 2.0) == 8.0
    assert multiply(-1.0, -1.0) == 1.0
    assert multiply(0.0, 5.0) == 0.0

def test_divide():
    assert divide(6.0, 3.0) == 2.0
    assert divide(-4.0, 2.0) == -2.0
    assert divide(0.0, 1.0) == 0.0

def test_divide_by_zero():
    with pytest.raises(ValueError):
        divide(5.0, 0.0)

def test_parse_input_valid():
    operation, a, b = _parse_input("add 3.0 4.0")
    assert operation == "add"
    assert a == 3.0
    assert b == 4.0

def test_parse_input_invalid_format():
    with pytest.raises(ValueError):
        _parse_input("add 3.0")

def test_parse_input_non_numeric_operands():
    with pytest.raises(ValueError):
        _parse_input("add three 4.0")
