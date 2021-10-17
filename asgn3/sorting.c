#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UINTLIMIT 4294967295
#define OPTIONS   "aeisqr:n:p:h"

/*bit m1ask to limit array elements to within 30 bits */
static const uint32_t bit_mask = 0x3fffffff;

/* define enumeration names to be added to set for functions to be run */
typedef enum { DEFAULT, INSERTION_SORT, HEAP_SORT, SHELL_SORT, QUICK_SORT, HELP } Commands;

int array_print(uint32_t *A, uint32_t length) {
    for (uint32_t counter = 1; counter < length; counter++) {
        printf("%13" PRIu32, A[counter]);
        if (counter % 5 == 0) {
            printf("\n");
        }
    }
    return 0;
}
int main(int argc, char **argv) {
    Set a = empty_set();
    int opt = 0;
    uint32_t seed = 13371453;
    uint32_t array_length = 100;
    uint32_t elements_to_print = 100;
    uint32_t uiarg;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch statement to add functions to the set for them to be run */
        switch (opt) {
        case 'a': {
            a = insert_set(INSERTION_SORT, a);
            a = insert_set(HEAP_SORT, a);
            a = insert_set(SHELL_SORT, a);
            a = insert_set(QUICK_SORT, a);
            break;
        }
        case 'e': {
            a = insert_set(HEAP_SORT, a);
            break;
        }
        case 'i': {
            a = insert_set(INSERTION_SORT, a);
            break;
        }
        case 's': {
            a = insert_set(SHELL_SORT, a);
            break;
        }
        case 'q': {
            a = insert_set(QUICK_SORT, a);
            break;
        }
        case 'r': {
            uiarg = atoi(optarg);
            if (uiarg <= 0 || uiarg > UINTLIMIT) {
                ;
            } else {
                seed = uiarg;
            }
            break;
        }
        case 'n': {
            uiarg = atoi(optarg);
            if (uiarg <= 0) {
                ;
            } else {
                array_length = uiarg;
            }
            break;
        }
        case 'p': {
            uiarg = atoi(optarg);
            if (uiarg <= 0) {
                ;
            } else {
                elements_to_print = uiarg;
            }
            break;
        }
        case 'h': {
            a = insert_set(HELP, a);
            break;
        }
        }
    }
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    srand(seed);

    /* generates array with random 30 bit numbers for each element */
    uint32_t *Array = (uint32_t *) calloc(array_length, sizeof(uint32_t));
    for (uint32_t element = 0; element < array_length; element++) {
        Array[element] = random() & bit_mask;
    }
    uint32_t *Unsorted_Array = (uint32_t *) calloc(array_length, sizeof(uint32_t));
    for (uint32_t element = 0; element < array_length; element++) {
        Unsorted_Array[element] = Array[element];
    }
    /* conditionals check if command put function in set to be run  */

    /* if help message is requested by the command prompt or no command is detected */
    if (member_set(HELP, a) || member_set(DEFAULT, a)) {
        fprintf(stdout, "SYNOPSIS\n");
        fprintf(stdout, "   A library of sorting algorithms.\n");
        fprintf(stdout, "USAGE\n");
        fprintf(stdout, "   ./sorting [-aeisqr:n:p:h] [-r seed] [-n length] [-p elements]\n\n");
        fprintf(stdout, "OPTIONS\n");
        fprintf(stdout, "  -a   Runs all sorting algorithms.\n");
        fprintf(stdout, "  -e   Runs heap sort algorithm.\n");
        fprintf(stdout, "  -i   Runs insertion sort algorithm.\n");
        fprintf(stdout, "  -s   Runs shell sort algorithm.\n");
        fprintf(stdout, "  -q   Runs quicksort algorithm.\n");
        fprintf(stdout, "  -r   Sets RNG seed. Default is 13371453.\n");
        fprintf(stdout, "  -n   Sets array length. Default is 100.\n");
        fprintf(stdout, "  -p   Sets number of elements to print. Default is 100.\n");
        fprintf(stdout, "  -h   Display program synopsis and usage.\n");
        exit(0);
    }
    /* if heap sort is requested by the command prompt */
    if (member_set(HEAP_SORT, a)) {
        heap_sort(&stats, Array, array_length);
        fprintf(stdout, "Heap Sort, %u elemeents, %lu moves, %lu compares\n", array_length,
            stats.moves, stats.compares);
        array_print(Array, elements_to_print);
    }
    reset(&stats);
    for (uint32_t element = 0; element < array_length; element++) {
        Array[element] = Unsorted_Array[element];
    }

    /* if shell sort is requested by the command prompt */
    if (member_set(SHELL_SORT, a)) {
        shell_sort(&stats, Array, array_length);
        fprintf(stdout, "Shell Sort, %u elements, %lu moves, %lu compares\n", array_length,
            stats.moves, stats.compares);
        array_print(Array, elements_to_print);
    }

    reset(&stats);
    for (uint32_t element = 0; element < array_length; element++) {
        Array[element] = Unsorted_Array[element];
    }

    /* if insertion sort is requested by the command prompt */
    if (member_set(INSERTION_SORT, a)) {
        insertion_sort(&stats, Array, array_length);
        fprintf(stdout, "Insertion Sort, %u elements, %lu moves, %lu compares\n", array_length,
            stats.moves, stats.compares);
        array_print(Array, elements_to_print);
    }
    reset(&stats);
    for (uint32_t element = 0; element < array_length; element++) {
        Array[element] = Unsorted_Array[element];
    }

    /* if quick sort is requested by the command prompt */
    if (member_set(QUICK_SORT, a)) {
        quick_sort(&stats, Array, array_length);
        fprintf(stdout, "Quick Sort, %u elements, %lu moves, %lu compares\n", array_length,
            stats.moves, stats.compares);
        array_print(Array, elements_to_print);
    }
    reset(&stats);
    for (uint32_t element = 0; element < array_length; element++) {
        Array[element] = Unsorted_Array[element];
    }

    /* free allocated memory */
    free(Array);
    free(Unsorted_Array);

    return 0;
}
