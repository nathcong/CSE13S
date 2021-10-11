#include "mathlib.h"

#include <stdio.h>

static int total_bbp_terms = 1;

/* this function calculates pi using the Bailey-Borwein-Plouffe formula */
double pi_bbp(void) {
    total_bbp_terms = 1;
    double fraction = 0.0;
    double exponential_fraction = 0.0;
    double current = 47.0 / 15.0;
    double previous = 0.0;
    unsigned long exponent = 1.0;
    int k = 1;
    while (absolute(current - previous) > EPSILON) {
        exponent *= 16.0;
        exponential_fraction = 1.0 / exponent;
        fraction = ((k * (120.0 * k + 151.0)) + 47.0)
                   / ((((k * ((k * ((k * (512 * k + 1024)) + 712)) + 194))) + 15));
        previous = current;
        current += (exponential_fraction * fraction);
        k++;
        total_bbp_terms++;
    }
    return current;
}

/* this function returns the number of terms computed by the pi_bbp function
 * until the epsilon limit was reached */
int pi_bbp_terms(void) {
    return total_bbp_terms;
}
