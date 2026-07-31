#ifndef CALC_INPUT_HPP
#define CALC_INPUT_HPP

#include <cstddef>

struct Calc_input {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void calc_input_init(Calc_input &s, std::size_t capacity);
void calc_input_push(Calc_input &s, int value);
bool calc_input_pop(Calc_input &s, int &value);
bool calc_input_peek(const Calc_input &s, int &value);
bool calc_input_is_empty(const Calc_input &s);
void calc_input_destroy(Calc_input &s);

#endif
