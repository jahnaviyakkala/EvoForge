#include <assert.h>
#include <stdio.h>
#include "secure_banking.h"

int main(void) {
    Secure_banking m;
    secure_banking_init(&m);
    assert(secure_banking_count(&m) == 0);
    assert(secure_banking_add_entry(&m, 42.0));
    assert(secure_banking_count(&m) == 1);
    printf("secure_banking automated tests passed successfully.\n");
    return 0;
}
