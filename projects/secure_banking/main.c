#include <stdio.h>
#include "secure_banking.h"

int main(void) {
    Secure_banking m;
    secure_banking_init(&m);
    printf("=== Secure Banking CLI ===\n");
    printf("Enter numbers to add (non-numeric to finish):\n");
    double val;
    printf("Input value: ");
    while (scanf("%lf", &val) == 1) {
        secure_banking_add_entry(&m, val);
        printf("Input value: ");
    }
    printf("Total entries recorded: %zu\n", secure_banking_count(&m));
    return 0;
}
