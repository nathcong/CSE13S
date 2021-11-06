#include "code.h"

#include "defines.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Code code_init(void) {
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
    if (c->top == MAX_CODE_SIZE) {
        return true;
    } else {
        return false;
    }
}

bool code_set_bit(Code *c, uint32_t i) {

}

bool code_clr_bit(Code *c, uint32_t i) {

}

bool code_get_bit(Code *c, uint32_t i) {

}

bool code_push_bit(Code *c, uint8_t bit) {

}

bool code_pop_bit(Code *c, uint8_t *bit) {

}

void code_print(Code *c) {

}
