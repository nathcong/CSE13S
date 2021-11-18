#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t pmultiply, qmultiply, random, totient, g;
    mpz_inits(random, pmultiply, qmultiply, totient, g, NULL);

    uint64_t pbits, qbits;

    /* calculate numbers needed for bits that go to p and q */
    pbits = rand() % ((2 * nbits) / 4);
    pbits = pbits + (nbits / 4);

    qbits = nbits - pbits;

    pbits += 1;
    qbits += 1;

    /* make prime numbers */
    make_prime(p, pbits, iters);
    make_prime(q, qbits, iters);

    /* n = pq */
    mpz_mul(n, p, q);

    /* totient  = (p - 1)(q - 1) */
    mpz_sub_ui(pmultiply, p, 1);
    mpz_sub_ui(qmultiply, q, 1);
    mpz_mul(totient, pmultiply, qmultiply);

    /* find usable e value */
    while ((mpz_cmp_ui(g, 1)) != 0) {
        mpz_urandomb(e, state, nbits);
        gcd(g, e, totient);
    }

    /* clear mpz variables */
    mpz_clears(random, pmultiply, qmultiply, totient, g, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    ;
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    ;
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    ;
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    ;
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    ;
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    ;
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    ;
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    ;
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    ;
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    ;
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    ;
}
