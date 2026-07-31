#include <stdio.h>
#include "miniature_sql.h"

int main(void) {
    Miniature_sql m;
    miniature_sql_init(&m);
    printf("=== Miniature Sql CLI ===\n");
    printf("Enter numbers to add (non-numeric to finish):\n");
    double val;
    printf("Input value: ");
    while (scanf("%lf", &val) == 1) {
        miniature_sql_add_entry(&m, val);
        printf("Input value: ");
    }
    printf("Total entries recorded: %zu\n", miniature_sql_count(&m));
    return 0;
}
