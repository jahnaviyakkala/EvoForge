#include <cassert>
#include <iostream>
#include "tictactow_game.hpp"

int main() {
    Tictactow_game s;
    tictactow_game_init(s, 4);
    assert(tictactow_game_is_empty(s));
    tictactow_game_push(s, 1);
    tictactow_game_push(s, 2);
    int val;
    assert(tictactow_game_peek(s, val) && val == 2);
    assert(tictactow_game_pop(s, val) && val == 2);
    assert(tictactow_game_pop(s, val) && val == 1);
    assert(tictactow_game_is_empty(s));
    tictactow_game_destroy(s);
    std::cout << "C++ tictactow_game tests passed." << std::endl;
    return 0;
}
