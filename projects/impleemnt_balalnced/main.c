#include <stdio.h>
#include "impleemnt_balalnced.h"

int main(void) {
    Impleemnt_balalnced m;
    impleemnt_balalnced_init(&m);
    printf("=== Impleemnt Balalnced CLI ===\n");
    printf("Enter numbers to add (non-numeric to finish):\n");
    double val;
    printf("Input value: ");
    while (scanf("%lf", &val) == 1) {
        impleemnt_balalnced_add_entry(&m, val);
        printf("Input value: ");
    }
    printf("Total entries recorded: %zu\n", impleemnt_balalnced_count(&m));
    return 0;
}
