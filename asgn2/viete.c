#include "mathlib.h"

#include <stdio.h>

int static total_viete_terms = 0;

/* this function calculates pi using Viete's formula */
double pi_viete(void) {
    total_viete_terms = 0;
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

/* this function returns the number of terms computed by the pi_viete function
 * until the epsilon limit was reached */
int pi_viete_factors(void) {
    return total_viete_terms;
}
