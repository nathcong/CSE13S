#include "node.h"
#include "stack.h"
#include "defines.h"
#include "code.h"
#include "header.h"
#include "io.h"
#include "huffman.h"
#include "pq.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {
    bool help = false;
    bool compression = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch statement to add functions to the set for them to be run */
        switch (opt) {
        case 'h': {
            help = true;
            break;
        }
        case 'v': {
            compression = true;
            break;
        }
        case 'i': {
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            break;
        }
        case 'o': {
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            break;
        }
        default: {
            help = true;
            break;
        }
        }
    }

    if (help == true) {
        fprintf(outfile, "SYNOPSIS\n");
        fprintf(outfile,
            "  A Huffman encoder.\n  Compresses a file using the Huffman coding algorithm.");
        fprintf(outfile, "USAGE\n");
        fprintf(outfile, "  ./encode [-hvi:o:] [-i infile] [-o outfile]\n\n");
        fprintf(outfile, "OPTIONS\n");
        fprintf(outfile, "  -v		Print compression statistics.\n");
        fprintf(outfile, "  -h		Program help message.\n");
        fprintf(outfile, "  -i infile	Input file to compress. Default is stdin.\n");
        fprintf(outfile, "  -o outfile 	Output file with compressed data. Default is stdout.\n");
        exit(0);
    }
    if (compression == true) {
        ;
    }
}
