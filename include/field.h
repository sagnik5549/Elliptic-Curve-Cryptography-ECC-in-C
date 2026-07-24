#ifndef FIELD_H
#define FIELD_H

#include <gmp.h>

/* Finite field arithmetic over GF(p).
 *
 * All operations are performed modulo the prime p.
 */


// Modular arithmetic

void field_mod(mpz_t result,
               const mpz_t a,
               const mpz_t p);

void field_add(mpz_t result,
               const mpz_t a,
               const mpz_t b,
               const mpz_t p);

void field_sub(mpz_t result,
               const mpz_t a,
               const mpz_t b,
               const mpz_t p);

void field_mul(mpz_t result,
               const mpz_t a,
               const mpz_t b,
               const mpz_t p);

int field_div(mpz_t result,
              const mpz_t a,
              const mpz_t b,
              const mpz_t p);

int field_inverse(mpz_t result,
                  const mpz_t a,
                  const mpz_t p);

void field_pow(mpz_t result,
               const mpz_t a,
               const mpz_t exponent,
               const mpz_t p);

int field_equal(const mpz_t a,
                const mpz_t b);

#endif