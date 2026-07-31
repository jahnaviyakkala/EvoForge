#include "secure_bank.h"

void secure_bank_init(Secure_bank *m) {
    if (m) m->count = 0;
}

bool secure_bank_add_entry(Secure_bank *m, double val) {
    if (!m || m->count >= 100) return false;
    m->data[m->count++] = val;
    return true;
}

size_t secure_bank_count(const Secure_bank *m) {
    return m ? m->count : 0;
}
