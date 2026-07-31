#include <stdio.h>
#include "secure_bank.h"

int main(void) {
    Secure_bank m;
    secure_bank_init(&m);
    printf("=== Secure Bank CLI ===\n");
    printf("Enter numbers to add (non-numeric to finish):\n");
    double val;
    printf("Input value: ");
    while (scanf("%lf", &val) == 1) {
        secure_bank_add_entry(&m, val);
        printf("Input value: ");
    }
    printf("Total entries recorded: %zu\n", secure_bank_count(&m));
    return 0;
}
