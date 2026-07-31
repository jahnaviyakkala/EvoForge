import pytest
from calculation_service import CalculationService

@pytest.fixture
def calc_service():
    return CalculationService()

def test_add(calc_service):
    assert calc_service.add(1, 2) == 3
    assert calc_service.add(-1, -1) == -2
    assert calc_service.add(0, 0) == 0
    assert calc_service.add(-5, 5) == 0

def test_subtract(calc_service):
    assert calc_service.subtract(5, 3) == 2
    assert calc_service.subtract(-1, 1) == -2
    assert calc_service.subtract(0, 0) == 0
    assert calc_service.subtract(-5, -5) == 0

def test_multiply(calc_service):
    assert calc_service.multiply(4, 3) == 12
    assert calc_service.multiply(-2, -2) == 4
    assert calc_service.multiply(0, 5) == 0
    assert calc_service.multiply(-5, 0) == 0

def test_divide(calc_service):
    assert calc_service.divide(8, 2) == 4
    assert calc_service.divide(-1, -1) == 1
    assert calc_service.divide(0, 5) == 0
    with pytest.raises(ValueError):
        calc_service.divide(5, 0)
