#include "mathlib.h"
#include <stdio.h>

unsigned long static total_euler_terms = 0;

double pi_euler(void) {
    unsigned long k = 1;
    unsigned long exponent = 0.0;
    double current = 0.0;
    double previous = 1.0;
    double term = 0.0;
    while (absolute(current - previous) > EPSILON) {
        exponent = k * k;
        previous = current;
        current += 1.0 / exponent;
        k++;
        total_euler_terms++;
    }
    term = sqrt_newton(6 * current);
    return term;
}

int pi_euler_terms(void) {
    return total_euler_terms;
}
