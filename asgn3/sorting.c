#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "aeisqr:n:p:h"

/*bit m1ask to limit array elements to within 30 bits */
static const uint32_t bit_mask = 0x3fffffff;

/* define enumeration names to be added to set for functions to be run */
typedef enum { INSERTION_SORT, HEAP_SORT, SHELL_SORT, QUICK_SORT, PRINT_ELEMENTS, HELP } Commands;

int main(int argc, char **argv) {
    Set a = empty_set();
    int opt = 0;
    unsigned int seed = 13371453 int array_length = 100;
    int elements_to_print = 100;
    while ((opt = getopt(argc, argc, OPTIONS)) != -1) {
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
            if (optopt <= 0 || optopt > UINT_MAX) {
                ;
            } else {
                seed = optopt;
            }
            break;
        }
        case 'n': {
            if (optopt <= 0) {
                ;
            } else {
                array_length = optopt;
            }
            break;
        }
        case 'p': {
            a = insert_set(PRINT_ELEMENTS, a);
            if (optopt <= 0) {
                ;
            } else {
                elements_to_print = optopt;
            }
            break;
        }
        case 'h': {
            a = insert_set(HELP, a);
            break;
        }
        default: {
            a = insert_set(HELP, a);
            break;
        }
        }
    }
    Stats *stats;
    stats->moves = 0;
    stats->compares = 0;

    srand(seed)

        /* generates array with random 30 bit numbers for each element */
        u_int32_t *Array
        = (uint32_t *) calloc(array_length, sizeof(uint32_t));
    for (uint32_t element = 0; element < array_length; element++) {
        Array[element] = random() & bit_mask;
    }

    /* conditionals check if command put function in set to be run  */
    if (member_set(HELP, a)) {
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
        exit();
    }
    if (member_set(HEAP_SORT, a)) {
        printf("1");
    }
    reset(&stats);

    if (member_set(SHELL_SORT, a)) {
        printf("2");
    }
    reset(&stats);

    if (member_set(INSERTION_SORT, a)) {
        printf("3");
    }
    reset(&stats);

    if (member_set(QUICK_SORT, a)) {
        printf("4");
    }
    reset(&stats);

    if (member_set(PRINT_ELEMENTS, a)) {
        print("5")
    }

    free(Array)

        return 0;
}
