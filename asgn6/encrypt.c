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
    FILE *pbfile;
    bool pub = false;
    char *username = getenv("USER");

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
	    pbfile = fopen(optarg, "r");
            if (pbfile == NULL) {
                fprintf(stderr, "Error: File could not be opened.\n");
                return -1;
            }
            pub = true;
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
        fprintf(stderr, "  Encrypts data using RSA encryption, decryption done by decrypt program.\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "  ./encrypt [-hvi:o:n:] [-i infile] [-o outfile] [-n pbfile]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "  -v	       Enable verbose printing.\n");
        fprintf(stderr, "  -h	       Program help message.\n");
        fprintf(stderr, "  -i infile    Input file with data to be encrypted. Default is stdin.\n");
        fprintf(stderr, "  -o outfile   Output file with encrypted data. Default is stdout.\n");
        fprintf(stderr, "  -n pbfile    Public key file. Default is rsa.pub.\n");
        exit(0);
    }

    /* if files not specified, open default files */
    if (pub == false) {
        pbfile = fopen("rsa.pub", "r");
        if (pbfile == NULL) {
            fprintf(stderr, "Error: File could not be opened.\n");
	    fclose(pbfile);
            fclose(infile);
            fclose(outfile);
            return -1;
        }
    }

    /* read public key */
    mpz_t modn, pube, signature, userstr;
    mpz_inits(modn, pube, signature, userstr, NULL);

    rsa_read_pub(modn, pube, signature, username, pbfile);

    /* verbose output if enabled */
    if (verbose == true) {
	gmp_fprintf(stderr, "user = %s\n", username);
	gmp_fprintf(stderr, "signature (%d bits) = %Zu\n", mpz_sizeinbase(signature, 2) - 1, signature);
	gmp_fprintf(stderr, "public modulus (%d bits) = %Zu\n", mpz_sizeinbase(modn, 2) - 1, modn);
        gmp_fprintf(stderr, "public exponent (%d bits) = %Zu\n", mpz_sizeinbase(pube, 2) - 1, pube);
    }

    /* convert username to mpz_t and verify */
    mpz_set_str(userstr, username, 62);
    
    if (rsa_verify(userstr, signature, pube, modn) == false) {
	fprintf(stderr, "Error: Signature could not be verified.");
        fclose(pbfile);
        fclose(infile);
        fclose(outfile);
	mpz_clears(modn, pube, signature, userstr, NULL);
	return -1;
    }

    /* encrypt file */
    rsa_encrypt_file(infile, outfile, modn, pube);

    /* close files and clear mpz variables */
    fclose(pbfile);
    fclose(infile);
    fclose(outfile);

    mpz_clears(modn, pube, signature, userstr, NULL);
}
