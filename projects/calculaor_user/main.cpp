#include <iostream>
#include "calculaor_user.hpp"

int main() {
    Calculaor_user s;
    calculaor_user_init(s, 4);
    calculaor_user_push(s, 10);
    int val;
    if (calculaor_user_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (calculaor_user_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    calculaor_user_destroy(s);
    return 0;
}
