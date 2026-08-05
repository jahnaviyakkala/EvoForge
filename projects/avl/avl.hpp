#ifndef AVL_HPP
#define AVL_HPP

#include <string>
#include <vector>

struct Avl {
    std::string name;
    std::vector<double> data;
};

void avl_init(Avl &m, const std::string &name);
void avl_add_entry(Avl &m, double val);
std::size_t avl_count(const Avl &m);
void avl_clear(Avl &m);

#endif
