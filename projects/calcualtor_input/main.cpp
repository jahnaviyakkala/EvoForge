#include <iostream>
#include "calcualtor_input.hpp"

int main() {
    Calcualtor_input s;
    calcualtor_input_init(s, 4);
    calcualtor_input_push(s, 10);
    int val;
    if (calcualtor_input_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (calcualtor_input_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    calcualtor_input_destroy(s);
    return 0;
}
