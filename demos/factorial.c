#include <stdio.h>
#include "utils.h" // Include your factorial functions

int main(void) {
    printf("Factorial Demonstration\n\n");

    // basic integer factorials
    printf("Basic Integer Factorials: (exact)\n");
    double result;

    factorial(0, &result);
    printf("0! = %.0f\n", result);

    factorial(20, &result);
    printf("20! = %.0f\n", result);

    // large numbers n > 20
    printf("\nLarge Number Handling: (approximate)\n");
    factorial(25, &result);
    printf("25! ≈ %.8g\n", result);

    // non integer factorials
    printf("\nNon-Integer Factorials: (gamma)\n");
    factorial(5.5, &result);
    printf("5.5! ≈ %.6f\n", result);

    // error handling
    printf("\nError Handling:\n");

    // negative numbers
    Status status = factorial(-2, &result);
    printf("Trying -2!: %s\n",
           (status == INVALID_INPUT) ? "Invalid Input" : "Unexpected Success");

    // double_t overflow
    status = factorial(200, &result);
    printf("Trying 200!: %s\n",
           (status == OVERFLOW) ? "Overflow" : "Unexpected Success");

    return 0;
}
