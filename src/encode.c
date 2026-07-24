#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

#include "encode.h"


/*
 * Encode one character using the
 * Try-and-Increment algorithm.
 */

int encode_character(ECPoint *encoded_point,
                     unsigned int *offset,
                     unsigned char character,
                     const EllipticCurve *curve)
{
    if (encoded_point == NULL ||
        offset == NULL ||
        curve == NULL)
    {
        fprintf(stderr,
                "Error: Invalid argument passed to encode_character().\n");

        return 0;
    }

    mpz_t x;
    mpz_t rhs;
    mpz_t lhs;
    mpz_t y;
    mpz_t temp;

    mpz_init(x);
    mpz_init(rhs);
    mpz_init(lhs);
    mpz_init(y);
    mpz_init(temp);

    mpz_set_ui(x, character);

    *offset = 0;

    while (mpz_cmp(x, curve->p) < 0)
    {
        /*
         * rhs = x³ + ax + b (mod p)
         */

        mpz_powm_ui(rhs,
                    x,
                    3,
                    curve->p);

        mpz_mul(temp,
                curve->a,
                x);

        mpz_add(rhs,
                rhs,
                temp);

        mpz_add(rhs,
                rhs,
                curve->b);

        mpz_mod(rhs,
                rhs,
                curve->p);

        /*
         * Search for y
         */

        for (mpz_set_ui(y, 0);
             mpz_cmp(y, curve->p) < 0;
             mpz_add_ui(y, y, 1))
        {
            mpz_powm_ui(lhs,
                        y,
                        2,
                        curve->p);

            if (mpz_cmp(lhs, rhs) == 0)
            {
                point_set(encoded_point,
                          x,
                          y);

                mpz_clear(x);
                mpz_clear(rhs);
                mpz_clear(lhs);
                mpz_clear(y);
                mpz_clear(temp);

                return 1;
            }
        }

        mpz_add_ui(x,
                   x,
                   1);

        (*offset)++;
    }

    mpz_clear(x);
    mpz_clear(rhs);
    mpz_clear(lhs);
    mpz_clear(y);
    mpz_clear(temp);

    fprintf(stderr,
            "Error: Unable to encode character.\n");

    return 0;
}


/*
 * Decode an encoded point back into
 * the original character.
 */

unsigned char decode_character(const ECPoint *encoded_point,
                               unsigned int offset)
{
    mpz_t value;

    mpz_init(value);

    mpz_sub_ui(value,
               encoded_point->x,
               offset);

    unsigned char character =
        (unsigned char)mpz_get_ui(value);

    mpz_clear(value);

    return character;
}