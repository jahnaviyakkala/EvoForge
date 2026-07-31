#include <assert.h>
#include <stdio.h>
#include "impleemnt_balalnced.h"

int main(void) {
    Impleemnt_balalnced m;
    impleemnt_balalnced_init(&m);
    assert(impleemnt_balalnced_count(&m) == 0);
    assert(impleemnt_balalnced_add_entry(&m, 42.0));
    assert(impleemnt_balalnced_count(&m) == 1);
    printf("impleemnt_balalnced automated tests passed successfully.\n");
    return 0;
}
