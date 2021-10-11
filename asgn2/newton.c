#include "mathlib.h"

#include <stdio.h>

static int total_newton_terms = 0;

/* this function computes the square root of the inputted argument x using the 
 * Newton-Raphson method */
double sqrt_newton(double x) {
    total_newton_terms = 0;
    double current = 1.0;
    double previous = 0.0;
    while (absolute((current - previous)) > EPSILON) {
        previous = current;
        current = 0.5 * (previous + (x / previous));
        total_newton_terms++;
    }
    return current;
}

/* this function returns the number of terms computed by the sqrt_newton function
 * until it reaches the epsilon limit */
int sqrt_newton_iters(void) {
    return total_newton_terms;
}
