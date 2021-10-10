#include "mathlib.h"

#include <stdio.h>

int static total_viete_terms = 0;
double pi_viete(void) {
    double term = 0.0;
    double numerator = 0;
    double current = 1.0;
    double previous = 0.0;
    int k = 1;
    while (absolute(current - previous) > EPSILON) {
        numerator = sqrt_newton(2 + numerator);
        previous = current;
        current *= numerator / 2;
        term = 2 / current;
        k++;
        total_viete_terms++;
    }
    return term;
}

int pi_viete_factors(void) {
    return total_viete_terms;
}
