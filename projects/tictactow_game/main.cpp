#include <iostream>
#include "tictactow_game.hpp"

int main() {
    Tictactow_game s;
    tictactow_game_init(s, 4);
    tictactow_game_push(s, 10);
    int val;
    if (tictactow_game_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (tictactow_game_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    tictactow_game_destroy(s);
    return 0;
}
