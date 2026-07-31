#include <cassert>
#include <iostream>
#include "high_performance.hpp"

int main() {
    High_performance m;
    high_performance_init(m, "test_session");
    assert(high_performance_count(m) == 0);
    high_performance_add_entry(m, 42.0);
    assert(high_performance_count(m) == 1);
    high_performance_clear(m);
    assert(high_performance_count(m) == 0);
    std::cout << "high_performance automated tests passed successfully." << std::endl;
    return 0;
}
