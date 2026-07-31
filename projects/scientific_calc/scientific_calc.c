#include "scientific_calc.h"
#include <stdlib.h>

void scientific_calc_init(Scientific_calc *s, size_t capacity) {
    if (!s) return;
    s->data = (int *)malloc(capacity * sizeof(int));
    s->size = 0;
    s->capacity = s->data ? capacity : 0;
}

void scientific_calc_push(Scientific_calc *s, int value) {
    if (!s) return;
    if (s->size >= s->capacity) {
        size_t new_cap = s->capacity == 0 ? 4 : s->capacity * 2;
        int *new_data = (int *)realloc(s->data, new_cap * sizeof(int));
        if (!new_data) return;
        s->data = new_data;
        s->capacity = new_cap;
    }
    s->data[s->size++] = value;
}

bool scientific_calc_pop(Scientific_calc *s, int *value) {
    if (!s || s->size == 0) return false;
    if (value) *value = s->data[--s->size];
    return true;
}

bool scientific_calc_peek(const Scientific_calc *s, int *value) {
    if (!s || s->size == 0) return false;
    if (value) *value = s->data[s->size - 1];
    return true;
}

bool scientific_calc_is_empty(const Scientific_calc *s) {
    return !s || s->size == 0;
}

void scientific_calc_destroy(Scientific_calc *s) {
    if (!s) return;
    free(s->data);
    s->data = NULL;
    s->size = s->capacity = 0;
}
