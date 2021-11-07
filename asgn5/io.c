#include "code.h"
#include "io.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

uint64_t bytes_read;
uint64_t bytes_written;

static uint8_t buf[BLOCK];
static uint32_t index = 0;
static uint32_t end = -1;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int current_bytes_read = 0;
    uint32_t block_bytes = 1;
    while (block_bytes > 0 && nbytes != current_bytes_read) {
        block_bytes = read(infile, buf, nbytes);
        current_bytes_read += block_bytes;
    }
    bytes_read += current_bytes_read;
    return current_bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int current_bytes_written = 0;
    uint32_t block_bytes = 1;
    while (block_bytes > 0 && nbytes != current_bytes_written) {
        block_bytes = write(outfile, buf, nbytes);
        current_bytes_written += block_bytes;
    }
    bytes_written += current_bytes_written;
    return current_bytes_written;
}

bool read_bit(int infile, uint8_t *bit) {
    if (index == 0) {
        uint64_t block_bytes = read_bytes(infile, buf, BLOCK);
        if (block_bytes < BLOCK) {
            end = block_bytes * 8 + 1;
        }
    }

    *bit = ((buf[index / 8]) >> index % 8) & 1;
    index += 1;

    if (index == BLOCK * 8) {
        index = 0;
    }

    if (index != end) {
        return true;
    } else {
        return false;
    }
}

void write_code(int outfile, Code *c) {
    uint32_t retrieved_bit;
    for (uint32_t i = 0; i < c->top; i++) {
        retrieved_bit = code_get_bit(c, i);
        if (retrieved_bit == 1) {
            code_set_bit(c, index);
        } else {
            code_clr_bit(c, index);
        }
        index++;

        if (index == BLOCK * 8) {
            flush_codes(outfile);
            index = 0;
        }
    }
}

void flush_codes(int outfile) {
    uint32_t byte_index = index / 8;
    if (index / 8 > 0) {
        write_bytes(outfile, buf, byte_index);
    }
}
