#include "tic_tac.hpp"
#include <cstdlib>
#include <new>

void tic_tac_init(Tic_tac &s, std::size_t capacity) {
    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));
    s.size = 0;
    s.capacity = s.data ? capacity : 0;
}

void tic_tac_push(Tic_tac &s, int value) {
    if (s.size >= s.capacity) {
        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;
        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));
        if (!new_data) return;
        s.data = new_data;
        s.capacity = new_cap;
    }
    s.data[s.size++] = value;
}

bool tic_tac_pop(Tic_tac &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[--s.size];
    return true;
}

bool tic_tac_peek(const Tic_tac &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[s.size - 1];
    return true;
}

bool tic_tac_is_empty(const Tic_tac &s) {
    return s.size == 0;
}

void tic_tac_destroy(Tic_tac &s) {
    std::free(s.data);
    s.data = nullptr;
    s.size = s.capacity = 0;
}
