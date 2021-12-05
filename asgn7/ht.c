#include "bst.h"
#include "ht.h"
#include "speck.h"
#include "salts.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

uint64_t lookups;

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = SALT_HASHTABLE_LO;
        ht->salt[1] = SALT_HASHTABLE_HI;
        ht->size = size;
        ht->trees = (Node **) calloc(size, sizeof(Node *));
        if (!ht->trees) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht && (*ht)->trees) {
        free((*ht)->trees);
        free(*ht);
        *ht = NULL;
    }
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t hash_index = hash(ht->salt, oldspeak) % ht->size;
    return bst_find(ht->trees[hash_index], oldspeak);
    lookups++;
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t hash_index = hash(ht->salt, oldspeak) % ht->size;
    bst_insert(ht->trees[hash_index], oldspeak, newspeak);
    lookups++;
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            count++;
        }
    }
    return count;
}

double ht_avg_bst_size(HashTable *ht) {
    double total_size = 0;
    double total_trees = ht_count(ht);
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            total_size += bst_size(ht->trees[i]);
        }
    }
    return (total_size / total_trees);
}

double ht_avg_bst_height(HashTable *ht) {
    double total_height = 0;
    double total_trees = ht_count(ht);
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            total_height += bst_height(ht->trees[i]);
        }
    }
    return (total_height / total_trees);
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            bst_print(ht->trees[i]);
            fprintf(stderr, "\n");
        }
    }
}
