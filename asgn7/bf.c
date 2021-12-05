#include "bv.h"
#include "bf.h"
#include "salts.h"

#include <stdbool.h>
#include <stdint.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = SALT_PRIMARY_LO;
        bf->primary[1] = SALT_PRIMARY_HI;
        bf->secondary[0] = SALT_SECONDARY_LO;
        bf->secondary[1] = SALT_SECONDARY_HI;
        bf->tertiary[0] = SALT_TERTIARY_LO;
        bf->tertiary[1] = SALT_TERTIARY_HI;
        bf->filter = bv_create(size);
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
        bv_delete(&(*bf)->filter);
        free(*bf);
        *bf = NULL;
    }
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_hash = hash(bf->primary, oldspeak);
    uint32_t secondary_hash = hash(bf->secondary, oldspeak);
    uint32_t tertiary_hash = hash(bf->tertiary, oldspeak);

    bv_set_bit(bf->filter, primary_hash);
    bv_set_bit(bf->filter, secondary_hash);
    bv_set_bit(bf->filter, tertiary_hash);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t primary_hash = hash(bf->primary, oldspeak);
    uint32_t secondary_hash = hash(bf->secondary, oldspeak);
    uint32_t tertiary_hash = hash(bf->tertiary, oldspeak);

    if ((bv_get_bit(bf->filter, primary_hash) == true)
        && (bv_get_bit(bf->filter, secondary_hash) == true)
        && (bv_get_bit(bf->filter, tertiary_hash) == true)) {
        return true;
    } else {
        return false;
    }
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        if (bv_get_bit(bf->filter, i) == true) {
            count++;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
