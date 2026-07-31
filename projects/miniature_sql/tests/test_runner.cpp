#include <cassert>
#include <iostream>
#include "miniature_sql.hpp"

int main() {
    Miniature_sql s;
    miniature_sql_init(s, 4);
    assert(miniature_sql_is_empty(s));
    miniature_sql_push(s, 1);
    miniature_sql_push(s, 2);
    int val;
    assert(miniature_sql_peek(s, val) && val == 2);
    assert(miniature_sql_pop(s, val) && val == 2);
    assert(miniature_sql_pop(s, val) && val == 1);
    assert(miniature_sql_is_empty(s));
    miniature_sql_destroy(s);
    std::cout << "C++ miniature_sql tests passed." << std::endl;
    return 0;
}
