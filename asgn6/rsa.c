#include "rsa.h"
#include "randstate.h"
#include "numtheory.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {
    	mpz_t pbits, qbits, pmultiply, qmultiply, random;
	mpz_inits(pbits, qbits, random, pmultiply, qmultiply, NULL);

	/* calculate numbers needed for bits that go to p and q */
	mpz_mul_ui(random, 2, nbits);

	urandomm(pbits, state, random);
	mpz_add(pbits, pbits, nbits);
	mpz_fdiv_q_ui(pbits, pbits, 4);

    	mpz_sub(qbits, nbits, pbits);

	/* make prime numbers */
	make_prime(p, pbits, iters);
    	make_prime(q, qbits, iters);

	/* n = (p - 1)(q - 1) */
	mpz_sub_ui(pmultiply, p, 1);
	mpz_sub_ui(qmultiply, q, 1);
	mpz_mul(n, pmultiply, qmultiply);

	/* find usable e value */

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
