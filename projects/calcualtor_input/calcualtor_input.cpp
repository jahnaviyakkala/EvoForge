#include "calcualtor_input.hpp"
#include <cstdlib>
#include <new>

void calcualtor_input_init(Calcualtor_input &s, std::size_t capacity) {
    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));
    s.size = 0;
    s.capacity = s.data ? capacity : 0;
}

void calcualtor_input_push(Calcualtor_input &s, int value) {
    if (s.size >= s.capacity) {
        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;
        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));
        if (!new_data) return;
        s.data = new_data;
        s.capacity = new_cap;
    }
    s.data[s.size++] = value;
}

bool calcualtor_input_pop(Calcualtor_input &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[--s.size];
    return true;
}

bool calcualtor_input_peek(const Calcualtor_input &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[s.size - 1];
    return true;
}

bool calcualtor_input_is_empty(const Calcualtor_input &s) {
    return s.size == 0;
}

void calcualtor_input_destroy(Calcualtor_input &s) {
    std::free(s.data);
    s.data = nullptr;
    s.size = s.capacity = 0;
}
