#include "quick.h"

#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

/* calculates pivot point seperating the two subarrays */
unsigned int partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    uint32_t j;
    uint32_t i = low - 1;
    for (j = low; j < high; j++) {
        if (cmp(stats, A[j - 1], A[high - 1]) == -1) {
            i++;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[high - 1]);
    return i + 1;
}

/* recursively calls the quick_sort implementation to continue the sort */
void quick_recursion(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t pivot = partition(stats, A, low, high);
        quick_recursion(stats, A, low, pivot - 1);
        quick_recursion(stats, A, pivot + 1, high);
    }
}

/* implementation of quick sort */
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_recursion(stats, A, 1, n);
}
