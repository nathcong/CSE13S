#include "mathlib.h"

#include <stdio.h>

static int total_newton_terms = 0;

double sqrt_newton(double x) {
    double y = 1.0;
    double z = 0.0;
    while (absolute((y - z)) > EPSILON) {
        z = y;
        y = 0.5 * (z + (x / z));
        ++total_terms;
    }
    return y;
}

int sqrt_newton_iters() {
    return total_newton_terms;
}
