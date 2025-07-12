#include "utils.h"
#include <stdbool.h>
#include <float.h>
#include <string.h>

Status lut_factorial(uint8_t n, double_t *result) {
    if (result == NULL)
        return INVALID_INPUT;
    if (n > 20)
        return INVALID_INPUT;
    *result = FACTORIAL_LUT[n];
    return SUCCESS;
}

// Γ(n) = (n-1)! or Γ(n+1)=n!
Status gamma_factorial(double_t n, double_t *result) {
    if (n < 0 || isnan(n) || isinf(n) || result == NULL)
        return INVALID_INPUT;
    if (n > 170)
        return OVERFLOW;
    *result = tgamma(n + 1);
    return SUCCESS;
}

// n!~√(2πn)(n/e)^n
// stirling's formula * (1+(1/12n))
Status stirlings_factorial(uint8_t n, double_t *result) {
    if (result == NULL)
        return INVALID_INPUT;
    if (n > 170)
        return OVERFLOW;
    const double_t term1 = sqrt(2 * PI * n);
    const double_t term2 = pow((n / exp(1.0)), n);
    const double_t term3 = 1.0 + (1.0 / (12 * n));
    *result = term1 * term2 * term3;
    return SUCCESS;
}

Status factorial(double_t n, double_t *result) {
    if (n < 0 || isnan(n) || isinf(n) || result == NULL)
        return INVALID_INPUT;
    if (n > 170)
        return OVERFLOW;

    double_t int_p;
    const double_t frac = modf(n, &int_p);
    const bool is_int = (fabs(frac) < DBL_EPSILON);

    if (is_int) {
        const uint8_t int_n = (uint8_t)int_p;

        if (n <= 20) {
            return lut_factorial(int_n, result);
        } else {
            return stirlings_factorial(int_n, result);
        }
    } else {
        return gamma_factorial(n, result);
    }
}

Status rsqrt(double_t n, double_t *result) {
    if (n < 0 || isnan(n) || isinf(n) || result == NULL)
        return INVALID_INPUT;

    const double_t threehalfs = 1.5;
    double_t y = n;
    int64_t i;

    memcpy(&i, &y, sizeof(double_t));

    // magic number for double_t (64-bit)
    i = 0x5fe6eb50c7b537a9 - (i >> 1);

    // copy bits back to double_t
    memcpy(&y, &i, sizeof(double_t));

    // Newton-Raphson iterations (3x for double_t precision)
    y = y * (threehalfs - (n * 0.5 * y * y));
    y = y * (threehalfs - (n * 0.5 * y * y));
    y = y * (threehalfs - (n * 0.5 * y * y));

    *result = y;
    return SUCCESS;
}
