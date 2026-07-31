#include <iostream>
#include "xox_game.hpp"

int main() {
    Xox_game s;
    xox_game_init(s, 4);
    xox_game_push(s, 10);
    int val;
    if (xox_game_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (xox_game_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    xox_game_destroy(s);
    return 0;
}
