#include "code.h"

#include "defines.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0x00;
    }
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}
bool code_full(Code *c) {
    if (c->top == ALPHABET) {
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        c->bits[i / 8] |= (1 << (i % 8));
        return true;
    } else {
        return false;
    }
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        c->bits[i / 8] &= (0 << (i % 8));
        return true;
    } else {
        return false;
    }
}

bool code_get_bit(Code *c, uint32_t i) {
    if (i < ALPHABET) {
        uint8_t retrieved_bit = ((c->bits[i / 8]) >> i % 8) & 1;
        if (retrieved_bit == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (c->top < ALPHABET) {
        if (bit == 1) {
            code_clr_bit(c, c->top);
        } else {
            code_clr_bit(c, c->top);
        }
        c->top++;
        return true;
    } else {
        return false;
    }
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (c->top != 0) {
        c->top--;
        *bit = code_get_bit(c, c->top);
        code_clr_bit(c, c->top);
        return true;
    } else {
        return false;
    }
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        fprintf(stdout, "%d", c->bits[i]);
    }
}
