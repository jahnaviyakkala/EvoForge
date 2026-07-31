#include <iostream>
#include "miniature_sql.hpp"

int main() {
    Miniature_sql s;
    miniature_sql_init(s, 4);
    miniature_sql_push(s, 10);
    int val;
    if (miniature_sql_peek(s, val)) std::cout << "Top: " << val << std::endl;
    while (miniature_sql_pop(s, val)) std::cout << "Popped: " << val << std::endl;
    miniature_sql_destroy(s);
    return 0;
}
