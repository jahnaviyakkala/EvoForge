#include <stdio.h>
#include "scientific_calc.h"

int main(void) {
    Scientific_calc s;
    scientific_calc_init(&s, 4);
    scientific_calc_push(&s, 10);
    int val;
    if (scientific_calc_peek(&s, &val)) printf("Top: %d\n", val);
    while (scientific_calc_pop(&s, &val)) printf("Popped: %d\n", val);
    scientific_calc_destroy(&s);
    return 0;
}
