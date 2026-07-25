#include <stdio.h>
#include "stack.h"

int main(void) {
    Stack s;
    stack_init(&s, 4);
    stack_push(&s, 10);
    int val;
    if (stack_peek(&s, &val)) printf("Top: %d\n", val);
    while (stack_pop(&s, &val)) printf("Popped: %d\n", val);
    stack_destroy(&s);
    return 0;
}
