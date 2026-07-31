#ifndef MINIATURE_SQL_HPP
#define MINIATURE_SQL_HPP

#include <cstddef>

struct Miniature_sql {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void miniature_sql_init(Miniature_sql &s, std::size_t capacity);
void miniature_sql_push(Miniature_sql &s, int value);
bool miniature_sql_pop(Miniature_sql &s, int &value);
bool miniature_sql_peek(const Miniature_sql &s, int &value);
bool miniature_sql_is_empty(const Miniature_sql &s);
void miniature_sql_destroy(Miniature_sql &s);

#endif
