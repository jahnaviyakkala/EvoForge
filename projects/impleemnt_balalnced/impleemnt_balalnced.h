#ifndef IMPLEEMNT_BALALNCED_H
#define IMPLEEMNT_BALALNCED_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    double data[100];
    size_t count;
} Impleemnt_balalnced;

void impleemnt_balalnced_init(Impleemnt_balalnced *m);
bool impleemnt_balalnced_add_entry(Impleemnt_balalnced *m, double val);
size_t impleemnt_balalnced_count(const Impleemnt_balalnced *m);

#endif
