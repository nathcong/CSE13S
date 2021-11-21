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
#include <limits.h>
#include <sys/stat.h>
#define OPTIONS "hvi:s:b:n:d:"

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    bool verbose = false;
    uint64_t seed = time(NULL);
    uint64_t uiarg = 0;
    uint64_t iters = 50;
    uint64_t nbits = 256;
    FILE *pbfile;
    FILE *pvfile;
    bool pub = false;
    bool priv = false;
    char *username;

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
        case 's': {
            uiarg = atoi(optarg);
            if (uiarg <= 0 || uiarg > ULLONG_MAX) {
                ;
            } else {
                seed = uiarg;
            }
            break;
        }
        case 'i': {
            uiarg = atoi(optarg);
            if (uiarg <= 0 || uiarg > ULLONG_MAX) {
                ;
            } else {
                iters = uiarg;
            }
            break;
        }
        case 'b': {
            uiarg = atoi(optarg);
            if (uiarg <= 0) {
                ;
            } else {
                nbits = uiarg;
            }
            break;
        }
        case 'n': {
            pbfile = fopen(optarg, "ab+");
            if (pbfile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            pub = true;
            break;
        }
        case 'd': {
            pvfile = fopen(optarg, "r");
            if (pvfile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            priv = true;
            break;
        }
        default: {
            help = true;
            break;
        }
        }
    }

    /* help message */
    if (help == true) {
        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "  Generates a pair of RSA public and private keys.\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./key [-hvb:i:n:d:s:] [-b bits] [-i iterations]\n  [-n pbfile] [-d "
                        "pvfile] [-s seed]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -v		  Enable verbose printing.\n");
        fprintf(stderr, "  -h		  Program help message.\n");
        fprintf(stderr, "  -b bits        Bits needed for public modulus n.\n");
        fprintf(stderr, "  -i iterations  Iterations to test primes. Default is 50.\n");
        fprintf(
            stderr, "  -s seed        Random seed for RNG. Default is time since UNIX epoch.\n");
        fprintf(stderr, "  -n pbfile	  Public key file. Default is rsa.pub.\n");
        fprintf(stderr, "  -d pvfile 	  Private key file. Default is rsa.priv.\n");
        exit(0);
    }

    /* if files not specified, open default files */
    if (pub == false) {
        pbfile = fopen("rsa.pub", "ab+");
        if (pbfile == NULL) {
            fprintf(stderr, "Error: File could not be opened.\n");
            return -1;
        }
    }

    if (priv == false) {
        pvfile = fopen("rsa.priv", "ab+");
        if (pbfile == NULL) {
            fprintf(stderr, "Error: File could not be opened.\n");
            return -1;
        }
    }

    /* set file permissions to 0600 */
    fchmod(fileno(pbfile), 0600);
    fchmod(fileno(pvfile), 0600);

    /* initialize randstate */
    randstate_init(seed);

    /* mpz_t initialization */
    mpz_t prime1, prime2, modn, pube, privp, privq, privkey, userstr, signature;
    mpz_inits(prime1, prime2, modn, pube, privp, privq, privkey, userstr, signature, NULL);

    /* create public and private keys */
    rsa_make_pub(prime1, prime2, modn, pube, nbits, iters);
    rsa_make_priv(privkey, pube, prime1, prime2);

    /* get username and compute signature*/
    username = getenv("USER");
    mpz_set_str(userstr, username, 62);
    rsa_sign(signature, userstr, privkey, modn);

    /* write keys to files */
    rsa_write_pub(modn, pube, signature, username, pbfile);
    rsa_write_priv(modn, privkey, pvfile);

    /* verbose output if enabled */
    if (verbose == true) {
        gmp_fprintf(
            stderr, "signature (%d bits) = %Zu\n", mpz_sizeinbase(signature, 2) - 1, signature);
        gmp_fprintf(stderr, "first prime (%d bits) = %Zu\n", mpz_sizeinbase(prime1, 2) - 1, prime1);
        gmp_fprintf(stderr, "second prime (%d bits) = %Zu\n", mpz_sizeinbase(prime2, 2) - 1, prime2);
        gmp_fprintf(stderr, "public modulus (%d bits) = %Zu\n", mpz_sizeinbase(modn, 2) - 1, modn);
        gmp_fprintf(stderr, "public exponent (%d bits) = %Zu\n", mpz_sizeinbase(pube, 2) - 1, pube);
        gmp_fprintf(stderr, "private key (%d bits) = %Zu\n", mpz_sizeinbase(privkey, 2) - 1, privkey);
    }

    /* memory clearing and file closing */
    mpz_clears(prime1, prime2, modn, pube, privp, privq, privkey, userstr, signature, NULL);
    fclose(pbfile);
    fclose(pvfile);
}
