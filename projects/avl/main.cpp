#include <iostream>
#include "avl.hpp"

int main() {
    Avl m;
    avl_init(m, "avl");
    std::cout << "=== Avl CLI ===\n";
    std::cout << "Enter numbers to add to module session (enter non-numeric to finish):\n";
    double val;
    while (std::cout << "Input value: " && (std::cin >> val)) {
        avl_add_entry(m, val);
    }
    std::cout << "Total entries recorded: " << avl_count(m) << std::endl;
    avl_clear(m);
    return 0;
}
