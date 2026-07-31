#include <assert.h>
#include <stdio.h>
#include "miniature_sql.h"

int main(void) {
    Miniature_sql m;
    miniature_sql_init(&m);
    assert(miniature_sql_count(&m) == 0);
    assert(miniature_sql_add_entry(&m, 42.0));
    assert(miniature_sql_count(&m) == 1);
    printf("miniature_sql automated tests passed successfully.\n");
    return 0;
}
