#include "high_performance.hpp"

void high_performance_init(High_performance &m, const std::string &name) {
    m.name = name;
    m.data.clear();
}

void high_performance_add_entry(High_performance &m, double val) {
    m.data.push_back(val);
}

std::size_t high_performance_count(const High_performance &m) {
    return m.data.size();
}

void high_performance_clear(High_performance &m) {
    m.data.clear();
}
