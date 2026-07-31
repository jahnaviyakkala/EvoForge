#ifndef CALCUALTOR_INPUT_HPP
#define CALCUALTOR_INPUT_HPP

#include <cstddef>

struct Calcualtor_input {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void calcualtor_input_init(Calcualtor_input &s, std::size_t capacity);
void calcualtor_input_push(Calcualtor_input &s, int value);
bool calcualtor_input_pop(Calcualtor_input &s, int &value);
bool calcualtor_input_peek(const Calcualtor_input &s, int &value);
bool calcualtor_input_is_empty(const Calcualtor_input &s);
void calcualtor_input_destroy(Calcualtor_input &s);

#endif
