#include "calc_inpout.hpp"
#include <cstdlib>
#include <new>

void calc_inpout_init(Calc_inpout &s, std::size_t capacity) {
    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));
    s.size = 0;
    s.capacity = s.data ? capacity : 0;
}

void calc_inpout_push(Calc_inpout &s, int value) {
    if (s.size >= s.capacity) {
        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;
        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));
        if (!new_data) return;
        s.data = new_data;
        s.capacity = new_cap;
    }
    s.data[s.size++] = value;
}

bool calc_inpout_pop(Calc_inpout &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[--s.size];
    return true;
}

bool calc_inpout_peek(const Calc_inpout &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[s.size - 1];
    return true;
}

bool calc_inpout_is_empty(const Calc_inpout &s) {
    return s.size == 0;
}

void calc_inpout_destroy(Calc_inpout &s) {
    std::free(s.data);
    s.data = nullptr;
    s.size = s.capacity = 0;
}
