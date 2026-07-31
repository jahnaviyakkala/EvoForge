#include "miniature_sql.h"

void miniature_sql_init(Miniature_sql *m) {
    if (m) m->count = 0;
}

bool miniature_sql_add_entry(Miniature_sql *m, double val) {
    if (!m || m->count >= 100) return false;
    m->data[m->count++] = val;
    return true;
}

size_t miniature_sql_count(const Miniature_sql *m) {
    return m ? m->count : 0;
}
