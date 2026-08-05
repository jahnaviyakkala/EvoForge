#include "avl.hpp"

void avl_init(Avl &m, const std::string &name) {
    m.name = name;
    m.data.clear();
}

void avl_add_entry(Avl &m, double val) {
    m.data.push_back(val);
}

std::size_t avl_count(const Avl &m) {
    return m.data.size();
}

void avl_clear(Avl &m) {
    m.data.clear();
}
