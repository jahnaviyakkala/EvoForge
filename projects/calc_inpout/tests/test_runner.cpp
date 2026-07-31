#include <cassert>
#include <iostream>
#include "calc_inpout.hpp"

int main() {
    Calc_inpout s;
    calc_inpout_init(s, 4);
    assert(calc_inpout_is_empty(s));
    calc_inpout_push(s, 1);
    calc_inpout_push(s, 2);
    int val;
    assert(calc_inpout_peek(s, val) && val == 2);
    assert(calc_inpout_pop(s, val) && val == 2);
    assert(calc_inpout_pop(s, val) && val == 1);
    assert(calc_inpout_is_empty(s));
    calc_inpout_destroy(s);
    std::cout << "C++ calc_inpout tests passed." << std::endl;
    return 0;
}
