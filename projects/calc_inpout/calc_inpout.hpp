#ifndef CALC_INPOUT_HPP
#define CALC_INPOUT_HPP

#include <cstddef>

struct Calc_inpout {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void calc_inpout_init(Calc_inpout &s, std::size_t capacity);
void calc_inpout_push(Calc_inpout &s, int value);
bool calc_inpout_pop(Calc_inpout &s, int &value);
bool calc_inpout_peek(const Calc_inpout &s, int &value);
bool calc_inpout_is_empty(const Calc_inpout &s);
void calc_inpout_destroy(Calc_inpout &s);

#endif
