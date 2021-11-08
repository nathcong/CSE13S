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
    bool compression_stats = false;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    uint8_t buf[BLOCK];
    struct stat perms;
    uint32_t existing_symbols = 0;
    uint64_t reading;
    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch statement to add functions to the set for them to be run */
        switch (opt) {
        case 'h': {
            help = true;
            break;
        }
        case 'v': {
            compression_stats = true;
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

    /* print help message */
    if (help == true) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr,
            "  A Huffman encoder.\n  Compresses a file using the Huffman coding algorithm.\n\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./encode [-hvi:o:] [-i infile] [-o outfile]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -v		Print compression statistics.\n");
        fprintf(stderr, "  -h		Program help message.\n");
        fprintf(stderr, "  -i infile	Input file to compress. Default is stdin.\n");
        fprintf(stderr, "  -o outfile 	Output file with compressed data. Default is stdout.\n");
        exit(0);
    }

    /* generate histogram array */
    uint64_t histogram[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        histogram[i] = 0;
    }
    histogram[0]++;
    histogram[255]++;

    /* writes stdin to temp file */
    if (lseek(infile, 0, SEEK_SET) == -1) {
        int tempfile = open("/tempencode.temp", O_TRUNC | O_CREAT | O_RDWR, 600);
        while ((reading = read_bytes(infile, buf, BLOCK)) > 0) {
            write_bytes(tempfile, buf, reading);
        }
        infile = tempfile;
    }

    /* seek and get file permissions */
    lseek(infile, 0, SEEK_SET);
    fstat(infile, &perms);
    fchmod(outfile, perms.st_mode);

    /* read file and get histogram data, count number of symbols */
    while ((reading = read_bytes(infile, buf, BLOCK)) > 0) {
        for (uint64_t i = 0; i < reading; i++) {
            histogram[buf[i]]++;
        }
    }
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (histogram[i] > 0) {
            existing_symbols++;
        }
    }

    /* build tree and build codes */
    Node *root = build_tree(histogram);
    Code codetable[ALPHABET];
    build_codes(root, codetable);

    /* header construction */
    Header head;
    head.magic = MAGIC;
    head.permissions = perms.st_mode;
    head.tree_size = (3 * existing_symbols) - 1;
    head.file_size = perms.st_size;
    write_bytes(outfile, (uint8_t *) &head, sizeof(head));

    /* write tree and code to outfile */
    dump_tree(outfile, root);
    lseek(infile, 0, SEEK_SET);

    /* lseek to write code to outfile */
    while ((reading = read_bytes(infile, buf, BLOCK)) > 0) {
        for (uint32_t i = 0; i < reading; i++) {
            write_code(outfile, &codetable[buf[i]]);
        }
    }
    flush_codes(outfile);

    /* print compression stats */
    if (compression_stats == true) {
        fprintf(stderr, "\nUncompressed file size: %" PRIu64 " bytes\n", bytes_read / 2);
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n", bytes_written);
        fprintf(
            stderr, "Space saving: %.5f%%\n", 100 * (1 - ((double) bytes_read / bytes_written)));
    }

    /* close files and free memory */
    close(infile);
    close(outfile);
    delete_tree(&root);
    node_delete(&root);
}
