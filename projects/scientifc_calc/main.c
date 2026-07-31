#include <stdio.h>
#include "scientifc_calc.h"

int main(void) {
    printf("=================================\n");
    printf("   Scientifc Calc CLI (C)\n");
    printf("=================================\n");
    printf("1. Add (+)\n2. Subtract (-)\n3. Multiply (*)\n4. Divide (/)\n5. Power\n6. Sqrt\n7. Factorial\n0. Exit\n");
    int choice;
    while (printf("\nSelect operation (0-7): ") && scanf("%d", &choice) == 1) {
        if (choice == 0) break;
        double a, b, res;
        if (choice >= 1 && choice <= 5) {
            printf("Enter first number: "); if (scanf("%lf", &a) != 1) break;
            printf("Enter second number: "); if (scanf("%lf", &b) != 1) break;
        } else if (choice == 6) {
            printf("Enter value: "); if (scanf("%lf", &a) != 1) break;
        }
        if (choice == 1) printf("Result: %f\n", scientifc_calc_add(a, b));
        else if (choice == 2) printf("Result: %f\n", scientifc_calc_subtract(a, b));
        else if (choice == 3) printf("Result: %f\n", scientifc_calc_multiply(a, b));
        else if (choice == 4) {
            if (scientifc_calc_divide(a, b, &res)) printf("Result: %f\n", res);
            else printf("Error: Division by zero!\n");
        }
        else if (choice == 5) {
            if (scientifc_calc_power(a, b, &res)) printf("Result: %f\n", res);
            else printf("Error: Invalid power!\n");
        }
        else if (choice == 6) {
            if (scientifc_calc_sqrt(a, &res)) printf("Result: %f\n", res);
            else printf("Error: Negative sqrt!\n");
        }
        else if (choice == 7) {
            int n; printf("Enter integer n: ");
            if (scanf("%d", &n) == 1 && scientifc_calc_factorial(n, &res)) printf("Result: %f\n", res);
            else printf("Error: Invalid factorial!\n");
        }
    }
    return 0;
}
