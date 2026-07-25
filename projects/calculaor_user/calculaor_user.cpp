#include "calculaor_user.hpp"
#include <cstdlib>
#include <new>

void calculaor_user_init(Calculaor_user &s, std::size_t capacity) {
    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));
    s.size = 0;
    s.capacity = s.data ? capacity : 0;
}

void calculaor_user_push(Calculaor_user &s, int value) {
    if (s.size >= s.capacity) {
        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;
        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));
        if (!new_data) return;
        s.data = new_data;
        s.capacity = new_cap;
    }
    s.data[s.size++] = value;
}

bool calculaor_user_pop(Calculaor_user &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[--s.size];
    return true;
}

bool calculaor_user_peek(const Calculaor_user &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[s.size - 1];
    return true;
}

bool calculaor_user_is_empty(const Calculaor_user &s) {
    return s.size == 0;
}

void calculaor_user_destroy(Calculaor_user &s) {
    std::free(s.data);
    s.data = nullptr;
    s.size = s.capacity = 0;
}
