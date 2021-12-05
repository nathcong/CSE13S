#include "bf.h"
#include "bst.h"
#include "bv.h"
#include "ht.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define OPTIONS "hst:f:"

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    bool stats = false;
    uint32_t uiarg = 0;
    uint32_t bloom_size = 1048576;
    uint32_t hash_size = 65536;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch statement to add functions to the set for them to be run */
        switch (opt) {
        case 'h': {
            help = true;
            break;
        }
        case 's': {
            stats = true;
            break;
        }
        case 't': {
            uiarg = atoi(optarg);
	    if (uiarg <= 0 || uiarg > ULONG_MAX) {
                fprintf(stderr, "Invalid value, reverting to default hash table size (2 ^ 16).\n");
            } else {
                hash_size = uiarg;
            }
            break;
        }
        case 'f': {
            uiarg = atoi(optarg);
	    if (uiarg <= 0 || uiarg > ULONG_MAX) {
                fprintf(stderr, "Invalid value, reverting to default bloom filter size (2 ^ 20).\n");
            } else {
                bloom_size = uiarg;
            }
            break;
        }
        default: {
            help = true;
            break;
        }
        }
    }

    /* help message */
    if (help == true) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "  A word filtering program for the GPRSC.\n");
	fprintf(stderr, "  Filters out and reports bad words parsed from stdin.\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./keygen [-hst:f:] [-t size] [-f size]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -v	      Print statistics.\n");
        fprintf(stderr, "  -h         Program help message.\n");
        fprintf(stderr, "  -t size    Hash table size. Default size is 2 ^ 16.\n");
        fprintf(stderr, "  -f size    Bloom filter size. Default size is 2 ^ 20.\n");
        exit(0);
    }

    /* initialize bloom filter and hash table */
    bf_create(bloom_size);
    ht_create(hash_size);

    /* scan list of badspeak words */


}
