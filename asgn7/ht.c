#include "bst.h"
#include "ht.h"

#include <stdint.h>

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
		ht->size[1] = SALT_HASHTABLE_HI;
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

}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {

}

uint32_t ht_count(HashTable *ht) {

}

double ht_avg_bst_size(HashTable *ht) {

}

double ht_avg_bst_height(HashTable *ht) {

}

void ht_print(HashTable *ht) {
	for (uint32_t i = 0; i < ht->size; i++) {
		if (ht->trees[i] != NULL) {
			;
		}
	}
}
