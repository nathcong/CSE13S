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
    bool decompression = false;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    uint8_t buf[BLOCK];
    Node *n;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch statement to add functions to the set for them to be run */
        switch (opt) {
        case 'h': {
            help = true;
            break;
        }
        case 'v': {
            decompression = true;
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
    /* read header and check compliances */
    Header head;
    read_bytes(infile, (uint8_t *) &head, sizeof(Header));

    if (head.magic != MAGIC) {
        fprintf(stderr, "Error: Magic number does not match, header unreadable.");
        return -1;
    }

    /* get file permissions */
    struct stat perms;
    fstat(infile, &perms);
    fchmod(outfile, head.permissions);

    /* rebuild tree from dump */
    uint8_t tree_dump[head.tree_size];
    read_bytes(infile, tree_dump, head.tree_size);
    Node *tree_root = rebuild_tree(head.tree_size, tree_dump);
    n = tree_root;

    /* File bit reading */
    uint8_t bit;
    uint32_t index = 0;
    while (bytes_written < head.file_size && read_bit(infile, &bit)) {
        if (bit == 1) {
            n = n->right;
        }
        if (bit == 0) {
            n = n->left;
        }
        if (n->left == NULL && n->right == NULL) {
            buf[index] = n->symbol;
            index++;

            if (index == BLOCK) {
                write_bytes(outfile, buf, BLOCK);
                index = 0;
            }
            n = tree_root;
        }
    }

    /* after finished reading bits, write leftover */
    write_bytes(outfile, buf, index);

    if (decompression == true) {
        fprintf(stderr, "\nCompressed file size: %" PRIu64 " bytes\n", bytes_read);
        fprintf(stderr, "Decompressed file size: %" PRIu64 " bytes\n", bytes_written);
        fprintf(stderr, "Space saving: %.5f%%", 100 * (1 - ((double) bytes_read / bytes_written)));
    }

    /* close files and free memory */
    close(infile);
    close(outfile);
    delete_tree(&tree_root);
    node_delete(&tree_root);
}
