#include <assert.h>
#include <stdio.h>
#include "scientifc_calc.h"

int main(void) {
    assert(scientifc_calc_add(5.0, 3.0) == 8.0);
    assert(scientifc_calc_subtract(10.0, 4.0) == 6.0);
    assert(scientifc_calc_multiply(2.0, 4.0) == 8.0);
    double res;
    assert(scientifc_calc_divide(10.0, 2.0, &res) && res == 5.0);
    assert(!scientifc_calc_divide(10.0, 0.0, &res));
    assert(scientifc_calc_power(2.0, 3.0, &res) && res == 8.0);
    assert(scientifc_calc_sqrt(16.0, &res) && res == 4.0);
    assert(!scientifc_calc_sqrt(-4.0, &res));
    assert(scientifc_calc_factorial(5, &res) && res == 120.0);
    printf("scientifc_calc automated tests passed successfully.\n");
    return 0;
}
