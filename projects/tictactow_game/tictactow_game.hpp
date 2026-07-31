#ifndef TICTACTOW_GAME_HPP
#define TICTACTOW_GAME_HPP

#include <cstddef>

struct Tictactow_game {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void tictactow_game_init(Tictactow_game &s, std::size_t capacity);
void tictactow_game_push(Tictactow_game &s, int value);
bool tictactow_game_pop(Tictactow_game &s, int &value);
bool tictactow_game_peek(const Tictactow_game &s, int &value);
bool tictactow_game_is_empty(const Tictactow_game &s);
void tictactow_game_destroy(Tictactow_game &s);

#endif
