#include <cassert>
#include <iostream>
#include "calcualtor_input.hpp"

int main() {
    Calcualtor_input s;
    calcualtor_input_init(s, 4);
    assert(calcualtor_input_is_empty(s));
    calcualtor_input_push(s, 1);
    calcualtor_input_push(s, 2);
    int val;
    assert(calcualtor_input_peek(s, val) && val == 2);
    assert(calcualtor_input_pop(s, val) && val == 2);
    assert(calcualtor_input_pop(s, val) && val == 1);
    assert(calcualtor_input_is_empty(s));
    calcualtor_input_destroy(s);
    std::cout << "C++ calcualtor_input tests passed." << std::endl;
    return 0;
}
