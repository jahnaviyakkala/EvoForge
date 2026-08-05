#include <iostream>
#include "xox.hpp"

int main() {
    Xox m;
    xox_init(m, "xox");
    std::cout << "=== Xox CLI ===\n";
    std::cout << "Enter numbers to add to module session (enter non-numeric to finish):\n";
    double val;
    while (std::cout << "Input value: " && (std::cin >> val)) {
        xox_add_entry(m, val);
    }
    std::cout << "Total entries recorded: " << xox_count(m) << std::endl;
    xox_clear(m);
    return 0;
}
