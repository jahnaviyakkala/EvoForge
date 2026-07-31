import pytest
from secure_bank import Secure_bank

def test_generic_object():
    obj = Secure_bank('test')
    obj.set_value('key1', 'val1')
    assert obj.has_key('key1')
    assert obj.get_value('key1') == 'val1'
    assert obj.get_value('missing', 'default') == 'default'
