#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    mpz_t pbits, qbits, pmultiply, qmultiply, random, bits, totient, g;
    mpz_inits(pbits, qbits, random, pmultiply, qmultiply, bits, totient, g, NULL);

    mpz_set_ui(bits, nbits);

    /* calculate numbers needed for bits that go to p and q */
    mpz_mul_ui(random, bits, 2);

    mpz_urandomm(pbits, state, random);
    mpz_add(pbits, pbits, bits);
    mpz_fdiv_q_ui(pbits, pbits, 4);

    mpz_sub(qbits, bits, pbits);

    /* need to turn pbits and qbits into uint64_t */
    uint64_t pbits64, qbits64;
    mpz_export(&pbits64, 0, -1, sizeof pbits64, 0, 0, pbits);
    mpz_export(&qbits64, 0, -1, sizeof qbits64, 0, 0, qbits);

    pbits64 += 1;
    qbits64 += 1;

    /* make prime numbers */
    make_prime(p, pbits64, iters);
    make_prime(q, qbits64, iters);

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
    mpz_clears(pbits, qbits, random, pmultiply, qmultiply, bits, totient, g, NULL);
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
