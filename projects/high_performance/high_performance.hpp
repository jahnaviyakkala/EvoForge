#ifndef HIGH_PERFORMANCE_HPP
#define HIGH_PERFORMANCE_HPP

#include <string>
#include <vector>

struct High_performance {
    std::string name;
    std::vector<double> data;
};

void high_performance_init(High_performance &m, const std::string &name);
void high_performance_add_entry(High_performance &m, double val);
std::size_t high_performance_count(const High_performance &m);
void high_performance_clear(High_performance &m);

#endif
