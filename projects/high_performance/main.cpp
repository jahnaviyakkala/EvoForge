#include <iostream>
#include "high_performance.hpp"

int main() {
    High_performance m;
    high_performance_init(m, "high_performance");
    std::cout << "=== High Performance CLI ===\n";
    std::cout << "Enter numbers to add to module session (enter non-numeric to finish):\n";
    double val;
    while (std::cout << "Input value: " && (std::cin >> val)) {
        high_performance_add_entry(m, val);
    }
    std::cout << "Total entries recorded: " << high_performance_count(m) << std::endl;
    high_performance_clear(m);
    return 0;
}
