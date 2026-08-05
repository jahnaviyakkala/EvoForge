#ifndef XOX_HPP
#define XOX_HPP

#include <string>
#include <vector>

struct Xox {
    std::string name;
    std::vector<double> data;
};

void xox_init(Xox &m, const std::string &name);
void xox_add_entry(Xox &m, double val);
std::size_t xox_count(const Xox &m);
void xox_clear(Xox &m);

#endif
