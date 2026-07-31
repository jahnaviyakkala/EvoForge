import pytest
from inventory_management import Inventory_management

def test_generic_object_operations():
    obj = Inventory_management('test')
    obj.set_value('key1', 'val1')
    assert obj.has_key('key1')
    assert obj.get_value('key1') == 'val1'
    assert obj.get_value('missing', 'default') == 'default'
