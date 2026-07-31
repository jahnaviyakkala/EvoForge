#include <cassert>
#include <iostream>
#include "generate_calcualtor.hpp"

int main() {
    Generate_calcualtor s;
    generate_calcualtor_init(s, 4);
    assert(generate_calcualtor_is_empty(s));
    generate_calcualtor_push(s, 1);
    generate_calcualtor_push(s, 2);
    int val;
    assert(generate_calcualtor_peek(s, val) && val == 2);
    assert(generate_calcualtor_pop(s, val) && val == 2);
    assert(generate_calcualtor_pop(s, val) && val == 1);
    assert(generate_calcualtor_is_empty(s));
    generate_calcualtor_destroy(s);
    std::cout << "C++ generate_calcualtor tests passed." << std::endl;
    return 0;
}
