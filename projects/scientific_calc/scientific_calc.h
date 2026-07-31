#ifndef SCIENTIFIC_CALC_H
#define SCIENTIFIC_CALC_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Scientific_calc;

void scientific_calc_init(Scientific_calc *s, size_t capacity);
void scientific_calc_push(Scientific_calc *s, int value);
bool scientific_calc_pop(Scientific_calc *s, int *value);
bool scientific_calc_peek(const Scientific_calc *s, int *value);
bool scientific_calc_is_empty(const Scientific_calc *s);
void scientific_calc_destroy(Scientific_calc *s);

#endif
