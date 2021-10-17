#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "stats.h"
#include "quick.h"

unsigned int partition(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
	uint32_t counter_2;
	uint32_t counter_1 = low - 1;
	for (counter_2 = low; counter_2 < high ; counter_2++) {
                if (cmp(stats, A[counter_2 - 1], A[high - 1]) == -1) {
                        counter_1++;
                        swap(stats, &A[counter_1 - 1], &A[counter_2 - 1]);
                }
        swap(stats, &A[counter_1], &A[high - 1]);
	}
	return counter_1 + 1;
}

void quick_recursion(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
	while (low < high) {
                uint32_t pivot = partition(stats, A, low, high);
		quick_recursion(stats, A, low, pivot - 1);
		quick_recursion(stats, A, pivot + 1, high);
        }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
	uint32_t low = 1;
	uint32_t high = n;
	quick_recursion(stats, A, low, high);
}
