#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define OPTIONS "hvi:s:b:n:d:"

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    bool verbose = false;
    
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        /* switch statement to add functions to the set for them to be run */
        switch (opt) {
        case 'h': {
            help = true;
            break;
        }
        case 'v': {
            verbose = true;
            break;
        }
	default: {
            help = true;
            break;
        }
        }
    }

}
