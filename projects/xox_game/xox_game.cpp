#include "xox_game.hpp"
#include <cstdlib>
#include <new>

void xox_game_init(Xox_game &s, std::size_t capacity) {
    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));
    s.size = 0;
    s.capacity = s.data ? capacity : 0;
}

void xox_game_push(Xox_game &s, int value) {
    if (s.size >= s.capacity) {
        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;
        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));
        if (!new_data) return;
        s.data = new_data;
        s.capacity = new_cap;
    }
    s.data[s.size++] = value;
}

bool xox_game_pop(Xox_game &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[--s.size];
    return true;
}

bool xox_game_peek(const Xox_game &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[s.size - 1];
    return true;
}

bool xox_game_is_empty(const Xox_game &s) {
    return s.size == 0;
}

void xox_game_destroy(Xox_game &s) {
    std::free(s.data);
    s.data = nullptr;
    s.size = s.capacity = 0;
}
