#include <assert.h>
#include <stdio.h>
#include "secure_bank.h"

int main(void) {
    Secure_bank m;
    secure_bank_init(&m);
    assert(secure_bank_count(&m) == 0);
    assert(secure_bank_add_entry(&m, 42.0));
    assert(secure_bank_count(&m) == 1);
    printf("secure_bank automated tests passed successfully.\n");
    return 0;
}
