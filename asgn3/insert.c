#include "insert.h"

#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/* implementation of the insertion sort */
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t i;
    uint32_t j;
    uint32_t temp;
    for (i = 0; i < n; i++) {
        j = i;
        temp = move(stats, A[i]);
        while (j > 0 && cmp(stats, temp, A[j - 1]) == -1) {
	    A[j] = move(stats, A[j - 1]);
            j -= 1;
        }
        A[j] = move(stats, temp);
    }
}
