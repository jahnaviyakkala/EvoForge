#include "miniature_sql.hpp"
#include <cstdlib>
#include <new>

void miniature_sql_init(Miniature_sql &s, std::size_t capacity) {
    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));
    s.size = 0;
    s.capacity = s.data ? capacity : 0;
}

void miniature_sql_push(Miniature_sql &s, int value) {
    if (s.size >= s.capacity) {
        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;
        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));
        if (!new_data) return;
        s.data = new_data;
        s.capacity = new_cap;
    }
    s.data[s.size++] = value;
}

bool miniature_sql_pop(Miniature_sql &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[--s.size];
    return true;
}

bool miniature_sql_peek(const Miniature_sql &s, int &value) {
    if (s.size == 0) return false;
    value = s.data[s.size - 1];
    return true;
}

bool miniature_sql_is_empty(const Miniature_sql &s) {
    return s.size == 0;
}

void miniature_sql_destroy(Miniature_sql &s) {
    std::free(s.data);
    s.data = nullptr;
    s.size = s.capacity = 0;
}
