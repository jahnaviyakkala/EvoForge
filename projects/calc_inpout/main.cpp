#include <iostream>
#include "calc_inpout.hpp"

int main() {
    Calc_inpout s;
    calc_inpout_init(s, 4);
    calc_inpout_push(s, 10);
    int val;
    if (calc_inpout_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (calc_inpout_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    calc_inpout_destroy(s);
    return 0;
}
