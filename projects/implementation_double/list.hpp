#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

struct List {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void list_init(List &s, std::size_t capacity);
void list_push(List &s, int value);
bool list_pop(List &s, int &value);
bool list_peek(const List &s, int &value);
bool list_is_empty(const List &s);
void list_destroy(List &s);

#endif
