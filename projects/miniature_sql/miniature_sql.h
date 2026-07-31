#ifndef MINIATURE_SQL_H
#define MINIATURE_SQL_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    double data[100];
    size_t count;
} Miniature_sql;

void miniature_sql_init(Miniature_sql *m);
bool miniature_sql_add_entry(Miniature_sql *m, double val);
size_t miniature_sql_count(const Miniature_sql *m);

#endif
