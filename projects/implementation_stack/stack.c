#include "stack.h"
#include <stdlib.h>

void stack_init(Stack *s, size_t capacity) {
    if (!s) return;
    s->data = (int *)malloc(capacity * sizeof(int));
    s->size = 0;
    s->capacity = s->data ? capacity : 0;
}

void stack_push(Stack *s, int value) {
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

bool stack_pop(Stack *s, int *value) {
    if (!s || s->size == 0) return false;
    if (value) *value = s->data[--s->size];
    return true;
}

bool stack_peek(const Stack *s, int *value) {
    if (!s || s->size == 0) return false;
    if (value) *value = s->data[s->size - 1];
    return true;
}

bool stack_is_empty(const Stack *s) {
    return !s || s->size == 0;
}

void stack_destroy(Stack *s) {
    if (!s) return;
    free(s->data);
    s->data = NULL;
    s->size = s->capacity = 0;
}
