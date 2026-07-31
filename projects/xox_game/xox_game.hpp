#ifndef XOX_GAME_HPP
#define XOX_GAME_HPP

#include <cstddef>

struct Xox_game {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void xox_game_init(Xox_game &s, std::size_t capacity);
void xox_game_push(Xox_game &s, int value);
bool xox_game_pop(Xox_game &s, int &value);
bool xox_game_peek(const Xox_game &s, int &value);
bool xox_game_is_empty(const Xox_game &s);
void xox_game_destroy(Xox_game &s);

#endif
