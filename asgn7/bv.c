#include "bv.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv) {
        bv->length = length;
        bv->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
        if (!bv->vector) {
            free(bv);
            bv = NULL;
            return NULL;
        }
        for (uint32_t i = 0; i < length; i++) {
            bv->vector[i] = 0x00;
        }
        return bv;
    } else {
        return NULL;
    }
}

void bv_delete(BitVector **bv) {
    if (*bv && (*bv)->vector) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        bv->vector[i / 8] |= (1 << (i % 8));
        return true;
    } else {
        return false;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        bv->vector[i / 8] &= (0 << (i % 8));
        return true;
    } else {
        return false;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    if (i < bv->length) {
        uint8_t retrieved_bit = ((bv->vector[i / 8]) >> i % 8) & 1;
        if (retrieved_bit == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

void bv_print(BitVector *bv) {
    for (uint32_t i = 0; i < bv->length; i++) {
        if (bv_get_bit(bv, i) == 1) {
            fprintf(stderr, "1\n");
        } else {
            fprintf(stderr, "0\n");
        }
    }
}
