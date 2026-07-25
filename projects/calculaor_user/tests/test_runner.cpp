#include <cassert>
#include <iostream>
#include "calculaor_user.hpp"

int main() {
    Calculaor_user s;
    calculaor_user_init(s, 4);
    assert(calculaor_user_is_empty(s));
    calculaor_user_push(s, 1);
    calculaor_user_push(s, 2);
    int val;
    assert(calculaor_user_peek(s, val) && val == 2);
    assert(calculaor_user_pop(s, val) && val == 2);
    assert(calculaor_user_pop(s, val) && val == 1);
    assert(calculaor_user_is_empty(s));
    calculaor_user_destroy(s);
    std::cout << "C++ calculaor_user tests passed." << std::endl;
    return 0;
}
