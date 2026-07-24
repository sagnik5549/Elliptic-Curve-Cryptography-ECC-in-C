#include <stdio.h>
#include <stdlib.h>

#include "scalar.h"


// Scalar Multiplication

// Compute R = k × P using the Double-and-Add algorithm
void scalar_multiply(ECPoint *R,
                     const mpz_t k,
                     const ECPoint *P,
                     const EllipticCurve *curve)
{
    ECPoint result;
    ECPoint current;

    point_init(&result);
    point_init(&current);

    /*
     * Initialize:
     *
     * result  = O
     * current = P
     */

    point_set_infinity(&result);
    point_copy(&current, P);

    // 0 × P = Point at Infinity

    if (mpz_cmp_ui(k, 0) == 0)
    {
        point_set_infinity(R);

        point_clear(&result);
        point_clear(&current);

        return;
    }

    // Verify that P lies on the curve

    if (!point_is_on_curve(P, curve))
    {
        fprintf(stderr, "Error: Point is not on the curve.\n");

        point_set_infinity(R);

        point_clear(&result);
        point_clear(&current);

        return;
    }
    /*
     * Make a local copy of k because
     * we repeatedly divide it by 2.
     */

    mpz_t scalar;

    mpz_init_set(scalar, k);

    // Double-and-Add Algorithm


    while (mpz_cmp_ui(scalar, 0) > 0)
    {
        /*
         * If current bit is 1:
         *
         * result = result + current
         */

        if (mpz_odd_p(scalar))
        {
            point_add(&result,
                      &result,
                      &current,
                      curve);
        }

        // current = 2 × current

        point_double(&current,
                     &current,
                     curve);

        // scalar = scalar / 2

        mpz_fdiv_q_2exp(scalar,
                        scalar,
                        1);
    }

    // Copy final result


    point_copy(R,
               &result);

    // Free allocated memory

    mpz_clear(scalar);

    point_clear(&result);
    point_clear(&current);
}