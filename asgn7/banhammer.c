#include "bf.h"
#include "bst.h"
#include "bv.h"
#include "ht.h"
#include "node.h"
#include "parser.h"
#include "speck.h"
#include "messages.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <regex.h>
#define OPTIONS        "hst:f:"
#define REG_EXPRESSION "[A-Za-z0-9_]+('|-)[A-Za-z0-9_]+)*"

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    bool stats = false;
    uint32_t uiarg = 0;
    uint32_t bloom_size = 1048576;
    uint32_t hash_size = 65536;
    FILE *badspeak;
    FILE *oldnewspeak;
    char bsbuf[1024];
    char osbuf[1024];
    char nsbuf[1024];
    regex_t regex;
    char *word = NULL;

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
            if (uiarg <= 0) {
                fprintf(stderr, "Invalid value, reverting to default hash table size (2 ^ 16).\n");
            } else {
                hash_size = uiarg;
            }
            break;
        }
        case 'f': {
            uiarg = atoi(optarg);
            if (uiarg <= 0) {
                fprintf(
                    stderr, "Invalid value, reverting to default bloom filter size (2 ^ 20).\n");
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
    BloomFilter *bf = bf_create(bloom_size);
    HashTable *ht = ht_create(hash_size);

    /* scan list of badspeak words and insert into bloom filter and hash table*/
    badspeak = fopen("badspeak.txt", "r");
    while (fscanf(badspeak, "%s\n", bsbuf) != EOF) {
        bf_insert(bf, bsbuf);
        ht_insert(ht, bsbuf, NULL);
    }
    fclose(badspeak);

    /* scan list of oldspeak and newspeak and insert into hash table */
    oldnewspeak = fopen("newspeak.txt", "r");
    while (fscanf(oldnewspeak, "%s %s\n", osbuf, nsbuf) != EOF) {
        bf_insert(bf, osbuf);
        ht_insert(ht, osbuf, nsbuf);
    }
    fclose(oldnewspeak);

    /* compile regex expression */
    if (regcomp(&regex, REG_EXPRESSION, REG_EXTENDED)) {
        fprintf(stderr, "Error: Regular expression couldn't compile.");
        return -1;
    }

    /* read words from input and determine if counseling and/or thoughtcrime is needed */
    /* bst to store words in violation */
    Node *mixed = bst_create();
    Node *bad = bst_create();

    while ((word = next_word(stdin, &regex))) {
        if (bf_probe(bf, word) == true) {
            Node *temp = ht_lookup(ht, word);
            /* if word exists in hash table and has newspeak equivalent (counseling) */
            if (temp != NULL && temp->newspeak != NULL) {
                bad = bst_insert(bad, temp->oldspeak, temp->newspeak);
            }
            /* if word exists in hash table and has no newspeak equivalent (thoughtcrime) */
            if (temp != NULL && temp->newspeak == NULL) {
                mixed = bst_insert(mixed, temp->oldspeak, temp->newspeak);
            }
        }
    }

    /* if stats is enabled, print and exit */
    if (stats == true) {
        double avg_branches = branches / lookups;
        double hash_load = 100 * (ht_count(ht) / ht_size(ht));
        double bloom_load = 100 * (bf_count(bf) / bf_size(bf));

        fprintf(stdout, "Average BST size: %lf\n", ht_avg_bst_size(ht));
        fprintf(stdout, "Average BST height: %lf\n", ht_avg_bst_height(ht));
        fprintf(stdout, "Average branches traversed: %lf\n", avg_branches);
        fprintf(stdout, "Hash table load: %lf\n", hash_load);
        fprintf(stdout, "Bloom filter load: %lf\n", bloom_load);
    }

    /* otherwise, print required message */
    else {
        /* if only counseling is required */
        if (bst_size(mixed) > 0 && bst_size(bad) == 0) {
            fprintf(stdout, "%s", goodspeak_message);
            bst_print(mixed);
        }
        /* if only thoughtcrime is detected */
        if (bst_size(mixed) == 0 && bst_size(bad) > 0) {
            fprintf(stdout, "%s", badspeak_message);
            bst_print(bad);
        }
        /* if both thoughtcrime and counseling are detected */
        if (bst_size(mixed) > 0 && bst_size(bad) > 0) {
            fprintf(stdout, "%s", mixspeak_message);
            bst_print(mixed);
            bst_print(bad);
        }
    }

    /* free memory */
    bst_delete(&bad);
    bst_delete(&mixed);
    ht_delete(&ht);
    bf_delete(&bf);
    regfree(&regex);
}
