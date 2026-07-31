#ifndef SECURE_BANKING_H
#define SECURE_BANKING_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    double data[100];
    size_t count;
} Secure_banking;

void secure_banking_init(Secure_banking *m);
bool secure_banking_add_entry(Secure_banking *m, double val);
size_t secure_banking_count(const Secure_banking *m);

#endif
