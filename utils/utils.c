#include "utils.h"
#include <stdbool.h>
#include <float.h>
#include <stdlib.h>

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
