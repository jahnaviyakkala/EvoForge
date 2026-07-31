import pytest
from calculator_cli import CalculatorCLI

@pytest.fixture
def cli():
    return CalculatorCLI()

def test_handle_operation(cli):
    assert cli.handle_operation("add", 1, 2) == 3
    assert cli.handle_operation("subtract", 5, 3) == 2
    assert cli.handle_operation("multiply", 4, 3) == 12
    assert cli.handle_operation("divide", 8, 2) == 4

def test_handle_operation_invalid(cli):
    with pytest.raises(ValueError):
        cli.handle_operation("invalid_op", 1, 2)
