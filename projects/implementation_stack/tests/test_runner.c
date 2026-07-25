#include <assert.h>
#include <stdio.h>
#include "stack.h"

int main(void) {
    Stack s;
    stack_init(&s, 4);
    assert(stack_is_empty(&s));
    stack_push(&s, 1);
    stack_push(&s, 2);
    int val;
    assert(stack_peek(&s, &val) && val == 2);
    assert(stack_pop(&s, &val) && val == 2);
    assert(stack_pop(&s, &val) && val == 1);
    assert(stack_is_empty(&s));
    stack_destroy(&s);
    printf("C stack tests passed.\n");
    return 0;
}
