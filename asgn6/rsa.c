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
    pbits = (rand() % ((2 * nbits) / 4))  + (nbits / 4);
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

/* writes public key into pbfile */
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%Zx\n", e);
    gmp_fprintf(pbfile, "%Zx\n", s);
    gmp_fprintf(pbfile, "%s\n", username);
}

/* reads public key from pbfile */
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%Zx\n", e);
    gmp_fscanf(pbfile, "%Zx\n", s);
    gmp_fscanf(pbfile, "%s\n", username);
}

/* makes private RSA key */
void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t ptemp, qtemp, totient;
    mpz_inits(ptemp, qtemp, totient, NULL);

    /* compute totient = (p - 1)(q - 1) */
    mpz_sub_ui(ptemp, p, 1);
    mpz_sub_ui(qtemp, q, 1);
    mpz_mul(totient, ptemp, qtemp);

    /* e mod totient */
    mod_inverse(d, e, totient);

    /* clear mpz variables */
    mpz_clears(ptemp, qtemp, totient, NULL);
}

/* writes private key into pvfile */
void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n", n);
    gmp_fprintf(pvfile, "%Zx\n", d);
}

/* reads private key from pvfile */
void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n", n);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t nbits, block, ciphertext, message;
    mpz_inits(nbits, block, ciphertext, message, NULL);

    /* get block size */
    mpz_set_ui(block, mpz_sizeinbase(n, 2));
    mpz_sub_ui(block, block, 1);
    mpz_fdiv_q_ui(block, block, 8);

    uint64_t blockint = mpz_get_ui(block);

    /* block awway memory allocation and set 0th element to 0xFF*/
    uint8_t *buf = (uint8_t *) calloc(blockint, sizeof(uint8_t));
    buf[0] = 0xFF;

    /* read bytes and encrypt until all bytes are read */
    int reading = 0;
    while (reading > 0) {
        reading = fread(&buf[1], sizeof(uint8_t), blockint - 1, infile);
        mpz_import(message, blockint - 1, 1, blockint - 1, 1, 0, buf);
        rsa_encrypt(ciphertext, message, e, n);
        gmp_fprintf(outfile, "%Zx\n", ciphertext);
    }

    /* clear mpz variables */
    mpz_clears(nbits, block, ciphertext, message, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t nbits, block, ciphertext, message;
    mpz_inits(nbits, block, ciphertext, message, NULL);

    /* get block size */
    mpz_set_ui(block, mpz_sizeinbase(n, 2));
    mpz_sub_ui(block, block, 1);
    mpz_fdiv_q_ui(block, block, 8);

    uint64_t blockint = mpz_get_ui(block);

    /* block awway memory allocation and set 0th element to 0xFF*/
    uint8_t *buf = (uint8_t *) calloc(blockint, sizeof(uint8_t));
    buf[0] = 0xFF;

    /* read bytes and decrypt until all bytes are read */
    int reading = 0;
    while (reading > 0) {
        reading = gmp_fscanf(infile, "%Zx\n", ciphertext);
        mpz_export(message, NULL, 1, blockint - 1, 1, 0, ciphertext);
        rsa_decrypt(message, ciphertext, d, n);
        gmp_fprintf(outfile, "%s\n", message);
    }

    /* clear mpz variables */
    mpz_clears(nbits, block, ciphertext, message, NULL);
}

/* create signature with private key and public mod */
void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

/* verifies signature */
bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_inits(t, NULL);

    pow_mod(t, s, e, n);

    /* returns true in t == m */
    if ((mpz_cmp(t, m)) == 0) {
        return true;
    } else {
        return false;
    }
}
