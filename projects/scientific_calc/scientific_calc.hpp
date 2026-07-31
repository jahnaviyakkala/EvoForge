#ifndef SCIENTIFIC_CALC_HPP
#define SCIENTIFIC_CALC_HPP

#include <cstddef>

struct Scientific_calc {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void scientific_calc_init(Scientific_calc &s, std::size_t capacity);
void scientific_calc_push(Scientific_calc &s, int value);
bool scientific_calc_pop(Scientific_calc &s, int &value);
bool scientific_calc_peek(const Scientific_calc &s, int &value);
bool scientific_calc_is_empty(const Scientific_calc &s);
void scientific_calc_destroy(Scientific_calc &s);

#endif
