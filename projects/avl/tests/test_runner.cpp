/*
 * Automated test suite for the AVL project.
 *
 * This file is compiled by the Makefile's `test` target and uses
 * non‑interactive `assert()` statements to verify the public APIs
 * defined in avl.hpp.  The C implementation of the AVL tree
 * (avl.c / avl.h) is not linked into this test runner because the
 * current build system only compiles .cpp sources for tests.
 *
 * To run the tests:
 *   make clean
 *   make test
 *
 * All assertions must pass; otherwise the program will abort and
 * `make test` will report a failure.
 */

#include <cassert>
#include <iostream>
#include "avl.hpp"

int main() {
    // ------------------------------------------------------------------
    // Test 1: Initialization
    // ------------------------------------------------------------------
    Avl m;
    avl_init(m, "test_avl");
    assert(m.name == std::string("test_avl"));
    assert(avl_count(m) == 0);          // vector should be empty after init

    // ------------------------------------------------------------------
    // Test 2: Adding entries
    // ------------------------------------------------------------------
    double values[] = {3.14, -42.0, 1e308, 0.0};
    for (double v : values) {
        avl_add_entry(m, v);
    }
    assert(avl_count(m) == sizeof(values)/sizeof(values[0]));

    // Verify that the stored values match what we inserted.
    // Since `data` is public in the struct, we can access it directly
    // for verification purposes.  The API itself does not expose
    // individual elements, but this test ensures internal consistency.
    for (std::size_t i = 0; i < sizeof(values)/sizeof(values[0]); ++i) {
        assert(m.data[i] == values[i]);
    }

    // ------------------------------------------------------------------
    // Test 3: Clearing the module
    // ------------------------------------------------------------------
    avl_clear(m);
    assert(avl_count(m) == 0);          // vector should be empty after clear

    // Adding again after clear to ensure state is reset correctly.
    avl_add_entry(m, 42.0);
    assert(avl_count(m) == 1);
    assert(m.data[0] == 42.0);

    std::cout << "All tests passed successfully.\n";
    return 0;
}
