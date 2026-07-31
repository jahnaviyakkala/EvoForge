#include "impleemnt_balalnced.h"

void impleemnt_balalnced_init(Impleemnt_balalnced *m) {
    if (m) m->count = 0;
}

bool impleemnt_balalnced_add_entry(Impleemnt_balalnced *m, double val) {
    if (!m || m->count >= 100) return false;
    m->data[m->count++] = val;
    return true;
}

size_t impleemnt_balalnced_count(const Impleemnt_balalnced *m) {
    return m ? m->count : 0;
}
