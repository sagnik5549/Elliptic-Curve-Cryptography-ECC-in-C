#include "field.h"


// Compute result = a mod p
void field_mod(mpz_t result,
               const mpz_t a,
               const mpz_t p)
{
    mpz_mod(result, a, p);

    if (mpz_sgn(result) < 0)
    {
        mpz_add(result, result, p);
    }
}


// Compute result = (a + b) mod p
void field_add(mpz_t result,
               const mpz_t a,
               const mpz_t b,
               const mpz_t p)
{
    mpz_add(result, a, b);

    field_mod(result, result, p);
}


// Compute result = (a - b) mod p
void field_sub(mpz_t result,
               const mpz_t a,
               const mpz_t b,
               const mpz_t p)
{
    mpz_sub(result, a, b);

    field_mod(result, result, p);
}


// Compute result = (a × b) mod p
void field_mul(mpz_t result,
               const mpz_t a,
               const mpz_t b,
               const mpz_t p)
{
    mpz_mul(result, a, b);

    field_mod(result, result, p);
}


/* Compute the modular inverse of a
 *
 * Returns:
 *      1 -> Inverse exists
 *      0 -> Inverse does not exist
 */
int field_inverse(mpz_t result,
                  const mpz_t a,
                  const mpz_t p)
{
    if (mpz_invert(result, a, p) == 0)
    {
        return 0;
    }

    field_mod(result, result, p);

    return 1;
}


// Compute result = (a / b) mod p
int field_div(mpz_t result,
              const mpz_t a,
              const mpz_t b,
              const mpz_t p)
{
    mpz_t inverse;

    mpz_init(inverse);

    if (!field_inverse(inverse, b, p))
    {
        mpz_clear(inverse);

        return 0;
    }

    field_mul(result, a, inverse, p);

    mpz_clear(inverse);

    return 1;
}


// Compute result = a^exponent mod p
void field_pow(mpz_t result,
               const mpz_t a,
               const mpz_t exponent,
               const mpz_t p)
{
    mpz_powm(result,
             a,
             exponent,
             p);
}


/* Compare two field elements
 * 
 * Returns:
 *      1 -> Equal
 *     0 -> Not equal
 */
int field_equal(const mpz_t a,
                const mpz_t b)
{
    return mpz_cmp(a, b) == 0;
}