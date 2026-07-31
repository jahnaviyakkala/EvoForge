#include <cassert>
#include <iostream>
#include "xox_game.hpp"

int main() {
    Xox_game s;
    xox_game_init(s, 4);
    assert(xox_game_is_empty(s));
    xox_game_push(s, 1);
    xox_game_push(s, 2);
    int val;
    assert(xox_game_peek(s, val) && val == 2);
    assert(xox_game_pop(s, val) && val == 2);
    assert(xox_game_pop(s, val) && val == 1);
    assert(xox_game_is_empty(s));
    xox_game_destroy(s);
    std::cout << "C++ xox_game tests passed." << std::endl;
    return 0;
}
