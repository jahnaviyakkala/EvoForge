#include <cassert>
#include <iostream>
#include "calc_input.hpp"

int main() {
    Calc_input s;
    calc_input_init(s, 4);
    assert(calc_input_is_empty(s));
    calc_input_push(s, 1);
    calc_input_push(s, 2);
    int val;
    assert(calc_input_peek(s, val) && val == 2);
    assert(calc_input_pop(s, val) && val == 2);
    assert(calc_input_pop(s, val) && val == 1);
    assert(calc_input_is_empty(s));
    calc_input_destroy(s);
    std::cout << "C++ calc_input tests passed." << std::endl;
    return 0;
}
