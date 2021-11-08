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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {
    bool help = false;
    bool compression = false;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int opt = 0;
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
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            break;
        }
        case 'o': {
            outfile = open(optarg, O_WRONLY | O_CREAT);
            if (outfile == -1) {
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
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr,
            "  A Huffman decoder.\n  Decompresses a file using the Huffman coding algorithm.\n\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./decode [-hvi:o:] [-i infile] [-o outfile]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -v          Print decompression statistics.\n");
        fprintf(stderr, "  -h          Program help message.\n");
        fprintf(stderr, "  -i infile   Input file to decompress. Default is stdin.\n");
        fprintf(stderr, "  -o outfile  Output file with decompressed data. Default is stdout.\n");
        exit(0);
    }
}
