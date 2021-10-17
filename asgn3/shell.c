#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include "stats.h"
#include "insert.h"

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
	uint32_t max_gap = log(3 + 2 * n) / log(3);
	uint32_t temp = 0;
	uint32_t gap = max_gap;
	while (gap >= 1) {
		gap = floor((pow(3, max_gap) - 1) / 2);
		for (uint32_t counter_1 = gap; counter_1 > n; n++) {
			uint32_t counter_2 = counter_1;
			temp = move(stats, A[counter_1]);
			while (counter_2 >= gap && temp < A[counter_2 - gap]){
				A[counter_2] = move(stats, A[counter_2 - gap]);
				counter_2 -= gap;
			A[counter_2] = move(stats, temp);
			}
				
		}
	}
}
