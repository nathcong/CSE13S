#include "mathlib.h"

#include <stdio.h>

static int total_e_terms = 1;

/* this function calculates Euler's number and returns the final
 * term calculated after the term exceeds the EPSILON limit of 1e-14  */
double e(void) {
    unsigned long factorial = 1.0;
    double current = 1.0;
    double previous = 0.0;
    int k = 1;
    while (absolute(current - previous) > EPSILON) {
        factorial *= k;
        previous = current;
        current += (1.0 / factorial);
        k++;
        total_e_terms++;
    }
    return current;
}

/* this function returns the number of terms computated by the e() function
 * until epsilon limit  was reached */
int e_terms(void) {
    return total_e_terms;
}
