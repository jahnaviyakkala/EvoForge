#include "generate_calcualtor.hpp"
#include <cstdlib>
#include <new>

void generate_calcualtor_init(Generate_calcualtor &s, std::size_t capacity) {
    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));
    s.size = 0;
    s.capacity = s.data ? capacity : 0;
}

void generate_calcualtor_push(Generate_calcualtor &s, int value) {
    if (s.size >= s.capacity) {
        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;
        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));
        if (!new_data) return;
        s.data = new_data;
        s.capacity = new_cap;
    }
    s.data[s.size++] = value;
}

bool generate_calcualtor_pop(Generate_calcualtor &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[--s.size];
    return true;
}

bool generate_calcualtor_peek(const Generate_calcualtor &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[s.size - 1];
    return true;
}

bool generate_calcualtor_is_empty(const Generate_calcualtor &s) {
    return s.size == 0;
}

void generate_calcualtor_destroy(Generate_calcualtor &s) {
    std::free(s.data);
    s.data = nullptr;
    s.size = s.capacity = 0;
}
