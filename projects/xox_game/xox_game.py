from typing import Any, Dict

class Xox_game:
    def __init__(self, name: str = 'default'):
        self.name = name
        self._data: Dict[str, Any] = {}

    def set_value(self, key: str, value: Any) -> None:
        self._data[key] = value

    def get_value(self, key: str, default: Any = None) -> Any:
        return self._data.get(key, default)

    def has_key(self, key: str) -> bool:
        return key in self._data
