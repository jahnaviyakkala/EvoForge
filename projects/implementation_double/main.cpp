#include <iostream>
#include "list.hpp"

int main() {
    List s;
    list_init(s, 4);
    list_push(s, 10);
    int val;
    if (list_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (list_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    list_destroy(s);
    return 0;
}
