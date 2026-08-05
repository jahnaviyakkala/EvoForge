#include "xox.hpp"

void xox_init(Xox &m, const std::string &name) {
    m.name = name;
    m.data.clear();
}

void xox_add_entry(Xox &m, double val) {
    m.data.push_back(val);
}

std::size_t xox_count(const Xox &m) {
    return m.data.size();
}

void xox_clear(Xox &m) {
    m.data.clear();
}
