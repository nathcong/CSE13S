#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

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


    if (help == true) {
	fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "  Generates a pair of RSA public and private keys.\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./key [-hvb:i:n:d:s:] [-b bits] [-i iterations]\n
		       	[-n pbfile] [-d pvfile] [-s seed]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -v		  Enable verbose printing.\n");
        fprintf(stderr, "  -h		  Program help message.\n");
	fprintf(stderr, "  -b bits        Bits needed for public modulus n.\n");
	fprintf(stderr, "  -i iterations  Iterations to test primes. Default is 50.\n");
	fprintf(stderr, "  -s seed        Random seed for RNG. Default is time since UNIX epoch.\n");
        fprintf(stderr, "  -n pbfile	  Public key file. Default is rsa.pub.\n");
        fprintf(stderr, "  -d pvfile 	  Private key file. Default is rsa.priv.\n");
        exit(0);
    }
}
