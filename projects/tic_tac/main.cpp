#include <iostream>
#include "tic_tac.hpp"

int main() {
    Tic_tac s;
    tic_tac_init(s, 4);
    tic_tac_push(s, 10);
    int val;
    if (tic_tac_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (tic_tac_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    tic_tac_destroy(s);
    return 0;
}
