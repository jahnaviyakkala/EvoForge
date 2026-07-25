#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Stack;

void stack_init(Stack *s, size_t capacity);
void stack_push(Stack *s, int value);
bool stack_pop(Stack *s, int *value);
bool stack_peek(const Stack *s, int *value);
bool stack_is_empty(const Stack *s);
void stack_destroy(Stack *s);

#endif
