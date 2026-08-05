#include <cassert>
#include "xox.hpp"
#include <string>

int main() {
    // ------------------------------------------------------------------
    // Test 1: Initialization
    // ------------------------------------------------------------------
    Xox m;
    xox_init(m, "test_module");
    assert(m.name == std::string("test_module"));
    assert(xox_count(m) == 0);
    assert(m.data.empty());

    // ------------------------------------------------------------------
    // Test 2: Adding entries (positive, negative, zero)
    // ------------------------------------------------------------------
    xox_add_entry(m, 1.5);
    xox_add_entry(m, -2.3);
    xox_add_entry(m, 0.0);

    assert(xox_count(m) == 3);
    assert(m.data.size() == 3);
    assert(m.data[0] == 1.5);
    assert(m.data[1] == -2.3);
    assert(m.data[2] == 0.0);

    // ------------------------------------------------------------------
    // Test 3: Boundary condition – large double value
    // ------------------------------------------------------------------
    const double large_val = 1e308;   // near DBL_MAX
    xox_add_entry(m, large_val);
    assert(xox_count(m) == 4);
    assert(m.data[3] == large_val);

    // ------------------------------------------------------------------
    // Test 4: Clearing the module
    // ------------------------------------------------------------------
    xox_clear(m);
    assert(xox_count(m) == 0);
    assert(m.data.empty());

    return 0;   // success
}
