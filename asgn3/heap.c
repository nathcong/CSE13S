#include "heap.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* obtains the largest child that diverges from a parent */
unsigned int max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;
    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) == 1) {
        return right;
    }
    return left;
}

/* fixes and reorganizes the heap to put the new largest element on top */
void heap_fix(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t greatest = max_child(stats, A, mother, last);

    while (mother <= floor(last / 2) && found == false) {
        if (cmp(stats, A[mother - 1], A[greatest - 1]) == -1) {
            swap(stats, &A[mother - 1], &A[greatest - 1]);
            mother = greatest;
            greatest = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}

/* constructs the heap so the heap sort process can begin */
void heap_build(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t father;
    for (father = floor(last / 2); father > first - 1; father--) {
        heap_fix(stats, A, father, last);
    }
}

/* implementation of heap sort */
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    heap_build(stats, A, first, last);
    for (uint32_t branch = last; first < branch; branch--) {
        swap(stats, &A[first - 1], &A[branch - 1]);
        heap_fix(stats, A, first, branch - 1);
    }
}
