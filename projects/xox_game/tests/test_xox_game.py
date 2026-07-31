import pytest
from xox_game import Xox_game

def test_generic_object():
    obj = Xox_game('test')
    obj.set_value('key1', 'val1')
    assert obj.has_key('key1')
    assert obj.get_value('key1') == 'val1'
    assert obj.get_value('missing', 'default') == 'default'
