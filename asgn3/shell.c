#include "insert.h"
#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* implementation of shelk sort */
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t max_gap = floor(log(3 + 2 * n) / log(3));
    uint32_t temp = 0;
    uint32_t gap = max_gap;
    uint32_t gap_count = max_gap;
    while (gap >= 1) {
        gap = floor((pow(3, gap_count) - 1) / 2);
        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            temp = move(stats, A[i]);
            while (j >= gap && cmp(stats, temp, A[j - gap]) == -1) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
        gap_count -= 1;
    }
}
