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
#define OPTIONS "hvi:o:n:"

int main(int argc, char **argv) {
    int opt = 0;
    bool help = false;
    bool verbose = false;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pvfile;
    bool priv = false;

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
        case 'i': {
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            break;
        }
        case 'o': {
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            break;
        }
        case 'n': {
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
        fprintf(
            stderr, "  Decrypts data using RSA decryption, encryption done by encrypt program.\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./decrypt [-hvi:o:n:] [-i infile] [-o outfile] [-n pvfile]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -v	       Enable verbose printing.\n");
        fprintf(stderr, "  -h	       Program help message.\n");
        fprintf(stderr, "  -i infile    Input file with data to be decrypted. Default is stdin.\n");
        fprintf(stderr, "  -o outfile   Output file with decrypted data. Default is stdout.\n");
        fprintf(stderr, "  -n pbfile    Private key file. Default is rsa.priv.\n");
        exit(0);
    }

    /* if files not specified, open default files */
    if (priv == false) {
        pvfile = fopen("rsa.priv", "r");
        if (pvfile == NULL) {
            fprintf(stderr, "Error: File could not be opened.\n");
            fclose(pvfile);
            fclose(infile);
            fclose(outfile);
            return -1;
        }
    }

    /* read private key */
    mpz_t modn, privkey;
    mpz_inits(modn, privkey, NULL);

    rsa_read_priv(modn, privkey, pvfile);

    /* verbose output if enabled */
    if (verbose == true) {
        gmp_fprintf(stderr, "public modulus (%d bits) = %Zu\n", mpz_sizeinbase(modn, 2) - 1, modn);
        gmp_fprintf(stderr, "private key (%d bits) = %Zu\n", mpz_sizeinbase(modn, 2) - 1, privkey);
    }

    /* decrypt file */
    rsa_decrypt_file(infile, outfile, modn, privkey);

    /* close files and clear mpz variables */
    fclose(pvfile);
    fclose(infile);
    fclose(outfile);

    mpz_clears(modn, privkey, NULL);
}
