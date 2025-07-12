#ifndef __UTILS_H__
#define __UTILS_H__

#include <math.h>
#include <stdint.h>

typedef enum {
    SUCCESS = 0,
    INVALID_INPUT = -1,
    OVERFLOW = -2,
} Status;

static const double_t PI = 3.14159265358979323846;

/*
 * Factorial computation
 */

// factorial lookup table upto 20!
// used for (0-20)! and with O(n) time complexity
static const uint64_t FACTORIAL_LUT[21] = {
    1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800,
    39916800, 479001600, 6227020800, 87178291200, 1307674368000,
    20922789888000, 355687428096000, 6402373705728000,
    121645100408832000, 2432902008176640000
};

// calculates factorial 0-20 using lookup table
Status lut_factorial(uint8_t n, double_t *result);

// uses the gamma function to calculate factorials for floats 20 < n < 170
// gamma function: Γ(n)=(n-1)! or Γ(n+1)=n!
Status gamma_factorial(double_t n, double_t *result);

// calculates factorial using stirling's approximation
// stirling's formula: n!~√(2πn)(n/e)^n [here e is euler's number]
// we will use 1st order correction for more refined approximation
// 1st order correction: stirling's formula * (1+(1/12n))
Status stirlings_factorial(uint8_t n, double_t *result);

// unified factorial computation, this will choose which algorithm to use given a specific input
// is_integer && n <= 20 -> lut_factorial
// is_integer && n >= 20 -> stirlings_factorial
// n !is_integer -> gamma_factorial
// can only calculate upto 170! after that double_t overflows
Status factorial(double_t n, double_t *result);

/*
 * Inverse square root
 */

// quake III fast inverse square root algorithm
Status rsqrt(double_t n, double_t *result);

#endif // !__UTILS_H__
