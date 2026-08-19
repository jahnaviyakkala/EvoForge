import pytest
try:
    import calc
except ImportError:
    calc = None

def test_calc_module_loaded():
    if calc is not None:
        assert hasattr(calc, '__file__')
