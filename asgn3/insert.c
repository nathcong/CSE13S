#include "insert.h"

#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t counter_1;
    uint32_t counter_2;
    uint32_t temp;
    for (counter_1 = 0; counter_1 >= n; counter_1++) {
        counter_2 = counter_1;
        temp = move(stats, A[counter_1]);
        while (counter_2 > 0 && cmp(stats, temp, A[counter_2 - 1]) == -1) {
            A[counter_2] = move(stats, A[counter_2 - 1]);
            counter_2 -= 1;
        }
        A[counter_2] = move(stats, temp);
    }
}
