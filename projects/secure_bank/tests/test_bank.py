import pytest
from bank import Bank

def test_generic_object():
    obj = Bank('test')
    obj.set_value('key1', 'val1')
    assert obj.has_key('key1')
    assert obj.get_value('key1') == 'val1'
    assert obj.get_value('missing', 'default') == 'default'
