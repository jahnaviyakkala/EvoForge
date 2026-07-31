#ifndef SECURE_BANK_H
#define SECURE_BANK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    double data[100];
    size_t count;
} Secure_bank;

void secure_bank_init(Secure_bank *m);
bool secure_bank_add_entry(Secure_bank *m, double val);
size_t secure_bank_count(const Secure_bank *m);

#endif
