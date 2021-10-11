#include "mathlib.h"

#include <stdio.h>

static int total_newton_terms = 0;

/* this function computes the square root of the inputted argument x using the 
 * Newton-Raphson method */
double sqrt_newton(double x) {
    total_newton_terms = 0;
    double y = 1.0;
    double z = 0.0;
    while (absolute((y - z)) > EPSILON) {
        z = y;
        y = 0.5 * (z + (x / z));
        ++total_newton_terms;
    }
    return y;
}

/* this function returns the number of terms computed by the sqrt_newton function
 * until it reaches the epsilon limit */
int sqrt_newton_iters() {
    return total_newton_terms;
}
