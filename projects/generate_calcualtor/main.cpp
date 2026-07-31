#include <iostream>
#include "generate_calcualtor.hpp"

int main() {
    Generate_calcualtor s;
    generate_calcualtor_init(s, 4);
    generate_calcualtor_push(s, 10);
    int val;
    if (generate_calcualtor_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (generate_calcualtor_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    generate_calcualtor_destroy(s);
    return 0;
}
