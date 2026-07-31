#include <cassert>
#include <iostream>
#include "tic_tac.hpp"

int main() {
    Tic_tac s;
    tic_tac_init(s, 4);
    assert(tic_tac_is_empty(s));
    tic_tac_push(s, 1);
    tic_tac_push(s, 2);
    int val;
    assert(tic_tac_peek(s, val) && val == 2);
    assert(tic_tac_pop(s, val) && val == 2);
    assert(tic_tac_pop(s, val) && val == 1);
    assert(tic_tac_is_empty(s));
    tic_tac_destroy(s);
    std::cout << "C++ tic_tac tests passed." << std::endl;
    return 0;
}
