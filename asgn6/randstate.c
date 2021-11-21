#include "randstate.h"

#include <stdint.h>
#include <gmp.h>

gmp_randstate_t state;

/* initialize random state with seed */
void randstate_init(uint64_t seed) {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

/* clear random state */
void randstate_clear(void) {
    gmp_randclear(state);
}
