#include <cassert>
#include <iostream>
#include "scientific_calc.hpp"

int main() {
    Scientific_calc s;
    scientific_calc_init(s, 4);
    assert(scientific_calc_is_empty(s));
    scientific_calc_push(s, 1);
    scientific_calc_push(s, 2);
    int val;
    assert(scientific_calc_peek(s, val) && val == 2);
    assert(scientific_calc_pop(s, val) && val == 2);
    assert(scientific_calc_pop(s, val) && val == 1);
    assert(scientific_calc_is_empty(s));
    scientific_calc_destroy(s);
    std::cout << "C++ scientific_calc tests passed." << std::endl;
    return 0;
}
