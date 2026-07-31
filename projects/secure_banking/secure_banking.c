#include "secure_banking.h"

void secure_banking_init(Secure_banking *m) {
    if (m) m->count = 0;
}

bool secure_banking_add_entry(Secure_banking *m, double val) {
    if (!m || m->count >= 100) return false;
    m->data[m->count++] = val;
    return true;
}

size_t secure_banking_count(const Secure_banking *m) {
    return m ? m->count : 0;
}
