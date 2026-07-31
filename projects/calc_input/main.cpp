#include <iostream>
#include "calc_input.hpp"

int main() {
    Calc_input s;
    calc_input_init(s, 4);
    calc_input_push(s, 10);
    int val;
    if (calc_input_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (calc_input_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    calc_input_destroy(s);
    return 0;
}
