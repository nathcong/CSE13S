#include "numtheory.h"
#include "randstate.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

/* gets the gcd of inputs a and b and stores output in d */
void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t originalb, originala, temp;
    mpz_inits(originalb, originala, temp, NULL);

    /* store original numbers to avoid changes */
    mpz_set(originala, a);
    mpz_set(originalb, b);

    /* gcd algorithm */
    while ((mpz_cmp_ui(b, 0)) != 0) {
        mpz_set(temp, b);
        mpz_mod(b, a, b);
        mpz_set(a, temp);
    }
    mpz_set(d, a);

    /* return a and b to original values */
    mpz_set(a, originala);
    mpz_set(b, originalb);

    /* free memory of temporary variables */
    mpz_clears(originala, originalb, temp, NULL);
}

/* computes inverse of a mod n and stores it in i */
void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r, tempr, t, tempt, q, originalr, originalt, timesr, timest;
    mpz_inits(r, tempr, t, tempt, q, originalr, originalt, timesr, timest, NULL);

    mpz_set(r, n);
    mpz_set(tempr, a);
    mpz_set_ui(t, 0);
    mpz_set_ui(tempt, 1);

    /* mod inverse algorithm */
    while ((mpz_cmp_ui(tempr, 0)) != 0) {
        mpz_fdiv_q(q, r, tempr);

        /* store values of r and t so calculations can be done without interference */
        mpz_set(originalr, r);
        mpz_set(originalt, t);

        mpz_set(r, tempr);

        mpz_mul(timesr, q, tempr);
        mpz_sub(tempr, originalr, timesr);

        mpz_set(t, tempt);

        mpz_mul(timest, q, tempt);
        mpz_sub(tempt, originalt, timest);
    }
    if ((mpz_cmp_ui(t, 0)) < 0) {
        mpz_add(t, t, n);
	mpz_set(i, t);
	mpz_clears(r, tempr, t, tempt, q, originalr, originalt, NULL);
	return;
    }

    /* no inverse, sets i to 0 */
    if ((mpz_cmp_ui(r, 1)) > 0) {
        mpz_set_ui(i, 0);
	mpz_clears(r, tempr, t, tempt, q, originalr, originalt, NULL);
	return;
    }

    mpz_set(i, t);

    /* free memory of temporary variables */
    mpz_clears(r, tempr, t, tempt, q, originalr, originalt, NULL);
}

/* computes modulus exponentation, where base^exponent mod modulus and stores output in out */
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t p, v, d, n;
    mpz_inits(p, v, d, n, NULL);

    mpz_set_ui(v, 1);
    mpz_set(p, base);
    mpz_set(d, exponent);
    mpz_set(n, modulus);

    /* power modulo algorithm */
    while ((mpz_cmp_ui(d, 0)) > 0) {
        if ((mpz_odd_p(d)) != 0) {
            mpz_mul(v, v, p);
            mpz_mod(v, v, n);
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, n);

        mpz_fdiv_q_ui(d, d, 2);
    }
    mpz_set(out, v);

    /* free memory of temporary variables */
    mpz_clears(p, v, d, n, NULL);
}

/* prime tester using the miller-rabin algorithm */
bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t a, r, s, y, tempn, modn, j, temps, two, random;
    mpz_inits(a, r, s, y, tempn, modn, j, temps, two, random, NULL);
    mpz_set_ui(two, 2);

    /* special cases */

    /* n is 3 */
    if ((mpz_cmp_ui(n, 3)) == 0) {
        mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);
        return true;
    }

    /* n is 2 */
    if ((mpz_cmp_ui(n, 2)) == 0) {
        mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);
        return true;
    }

    /* n is 1 */
    if ((mpz_cmp_ui(n, 1)) == 0) {
        mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);
        return false;
    }

    /* n is 0 */
    if ((mpz_cmp_ui(n, 0)) == 0) {
        mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);
        return false;
    }

    /* if number is even */
    if ((mpz_even_p(n)) != 0) {
        mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);
        return false;
    }

    /* miller rabin test */
    mpz_sub_ui(tempn, n, 1);

    mpz_set(r, tempn);
    while ((mpz_even_p(r)) != 0) {
        mpz_fdiv_q_ui(r, r, 2);
        mpz_add_ui(s, s, 1);
    }

    mpz_sub_ui(temps, s, 1);

    for (uint64_t i = 1; i <= iters; i++) {
	mpz_sub_ui(random, n, 3);
        mpz_urandomm(a, state, random);
	mpz_add_ui(a, a, 2);

        pow_mod(y, a, r, n);
        if (((mpz_cmp_ui(y, 1)) != 0) && ((mpz_cmp(y, tempn)) != 0)) {
            mpz_set_ui(j, 1);

            while (((mpz_cmp(j, temps)) <= 0) && ((mpz_cmp(y, tempn)) != 0)) {
                pow_mod(y, y, two, n);
                if ((mpz_cmp_ui(y, 1)) == 0) {
                    mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if ((mpz_cmp(y, tempn)) != 0) {
                mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);
                return false;
            }
        }
    }
    /* free memory of temporary variables and RNG */
    mpz_clears(a, r, s, y, tempn, j, temps, two, modn, random, NULL);

    /* return true, number is prime */
    return true;
}

/* generates a prime number that is bits bits long and stores it in p */
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t bitnum;
    mpz_init(bitnum);

    /* maximum value */
    mpz_ui_pow_ui(bitnum, 2, bits);

    /* prime test */
    while (is_prime(p, iters) == false) {
        mpz_urandomm(p, state, bitnum);
    }
}
