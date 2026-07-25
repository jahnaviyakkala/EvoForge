#include <cassert>
#include <iostream>
#include "list.hpp"

int main() {
    List s;
    list_init(s, 4);
    assert(list_is_empty(s));
    list_push(s, 1);
    list_push(s, 2);
    int val;
    assert(list_peek(s, val) && val == 2);
    assert(list_pop(s, val) && val == 2);
    assert(list_pop(s, val) && val == 1);
    assert(list_is_empty(s));
    list_destroy(s);
    std::cout << "C++ list tests passed." << std::endl;
    return 0;
}
