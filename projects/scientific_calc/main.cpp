#include <iostream>
#include "scientific_calc.hpp"

int main() {
    Scientific_calc s;
    scientific_calc_init(s, 4);
    scientific_calc_push(s, 10);
    int val;
    if (scientific_calc_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (scientific_calc_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    scientific_calc_destroy(s);
    return 0;
}
