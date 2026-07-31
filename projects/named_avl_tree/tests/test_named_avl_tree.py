import pytest
from named_avl_tree import Named_avl_tree

def test_generic_object():
    obj = Named_avl_tree('test')
    obj.set_value('key1', 'val1')
    assert obj.has_key('key1')
    assert obj.get_value('key1') == 'val1'
    assert obj.get_value('missing', 'default') == 'default'
