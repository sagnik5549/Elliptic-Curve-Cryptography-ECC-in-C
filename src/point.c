#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

#include "point.h"
#include "curve.h"
#include "field.h"


// Point Management

// Initialize a point
void point_init(ECPoint *P)
{
    mpz_init(P->x);
    mpz_init(P->y);

    P->infinity = 0;
}


// Release allocated GMP memory
void point_clear(ECPoint *P)
{
    mpz_clear(P->x);
    mpz_clear(P->y);
}


// Copy one point to another
void point_copy(ECPoint *dest,
                const ECPoint *src)
{
    mpz_set(dest->x, src->x);
    mpz_set(dest->y, src->y);

    dest->infinity = src->infinity;
}


// Assign point coordinates
void point_set(ECPoint *P,
               const mpz_t x,
               const mpz_t y)
{
    mpz_set(P->x, x);
    mpz_set(P->y, y);

    P->infinity = 0;
}


// Set point at infinity
void point_set_infinity(ECPoint *P)
{
    mpz_set_ui(P->x, 0);
    mpz_set_ui(P->y, 0);

    P->infinity = 1;
}


// Point State

// Check whether a point is at infinity
int point_is_infinity(const ECPoint *P)
{
    return P->infinity;
}


// Point Comparison


// Compare two points
int point_equal(const ECPoint *P,
                const ECPoint *Q)
{
    if (P->infinity != Q->infinity)
        return 0;

    if (P->infinity)
        return 1;

    return (mpz_cmp(P->x, Q->x) == 0) &&
           (mpz_cmp(P->y, Q->y) == 0);
}


// Point Validation


// Check whether a point lies on the elliptic curve
int point_is_on_curve(const ECPoint *P,
                      const EllipticCurve *curve)
{
    if (point_is_infinity(P))
    {
        return 1;
    }

    mpz_t lhs;
    mpz_t rhs;
    mpz_t temp;

    mpz_inits(lhs,
              rhs,
              temp,
              NULL);

    // lhs = y^2 mod p 

    field_mul(lhs,
              P->y,
              P->y,
              curve->p);

    // rhs = x^3 + ax + b mod p

    field_mul(rhs,
              P->x,
              P->x,
              curve->p);

    field_mul(rhs,
              rhs,
              P->x,
              curve->p);

    field_mul(temp,
              curve->a,
              P->x,
              curve->p);

    field_add(rhs,
              rhs,
              temp,
              curve->p);

    field_add(rhs,
              rhs,
              curve->b,
              curve->p);

    int result = field_equal(lhs,
                             rhs);

    mpz_clears(lhs,
               rhs,
               temp,
               NULL);

    return result;
}


// Point Arithmetic


// Compute R = -P
void point_negate(ECPoint *R,
                  const ECPoint *P,
                  const EllipticCurve *curve)
{
    // Point at infinity 

    if (point_is_infinity(P))
    {
        point_set_infinity(R);
        return;
    }

    // Allow R == P 

    if (R != P)
    {
        mpz_set(R->x, P->x);
    }

    /*
     * y = -y mod p
     *    = p - y (mod p)
     */

    field_sub(R->y,
              curve->p,
              P->y,
              curve->p);

    R->infinity = 0;
}


// Compute R = 2P
void point_double(ECPoint *R,
                  const ECPoint *P,
                  const EllipticCurve *curve)
{
    // Point at infinity 

    if (point_is_infinity(P))
    {
        point_set_infinity(R);
        return;
    }

    /*
     * If y = 0 then the tangent is vertical,
     * therefore 2P = O.
     */

    if (mpz_cmp_ui(P->y, 0) == 0)
    {
        point_set_infinity(R);
        return;
    }

    mpz_t lambda;
    mpz_t numerator;
    mpz_t denominator;
    mpz_t x3;
    mpz_t y3;
    mpz_t temp;

    mpz_inits(lambda,
              numerator,
              denominator,
              x3,
              y3,
              temp,
              NULL);

    // numerator = 3x^2 + a


    field_mul(temp,
              P->x,
              P->x,
              curve->p);

    mpz_mul_ui(temp,
               temp,
               3);

    field_mod(temp,
              temp,
              curve->p);

    field_add(numerator,
              temp,
              curve->a,
              curve->p);

    // denominator = 2y


    mpz_mul_ui(denominator,
               P->y,
               2);

    field_mod(denominator,
              denominator,
              curve->p);

    // lambda = numerator / denominator


    if (!field_div(lambda,
                   numerator,
                   denominator,
                   curve->p))
    {
        point_set_infinity(R);

        mpz_clears(lambda,
                   numerator,
                   denominator,
                   x3,
                   y3,
                   temp,
                   NULL);

        return;
    }

    /*
     * x3 = λ² − 2x
     */

    field_mul(x3,
              lambda,
              lambda,
              curve->p);

    field_sub(x3,
              x3,
              P->x,
              curve->p);

    field_sub(x3,
              x3,
              P->x,
              curve->p);

    /*
     * y3 = λ(x − x3) − y
     */

    field_sub(temp,
              P->x,
              x3,
              curve->p);

    field_mul(temp,
              lambda,
              temp,
              curve->p);

    field_sub(y3,
              temp,
              P->y,
              curve->p);

    /*
     * Copy result
     */

    mpz_set(R->x, x3);
    mpz_set(R->y, y3);

    R->infinity = 0;

    mpz_clears(lambda,
               numerator,
               denominator,
               x3,
               y3,
               temp,
               NULL);
}


// Compute R = P + Q
void point_add(ECPoint *R,
               const ECPoint *P,
               const ECPoint *Q,
               const EllipticCurve *curve)
{
    // Special Cases

    // O + Q = Q

    if (point_is_infinity(P))
    {
        point_copy(R, Q);
        return;
    }

    // P + O = P

    if (point_is_infinity(Q))
    {
        point_copy(R, P);
        return;
    }

    /*
     * P = -Q
     * Same x-coordinate but opposite y-coordinate
     */

    if (mpz_cmp(P->x, Q->x) == 0)
    {
        // Same point -> point doubling 

        if (mpz_cmp(P->y, Q->y) == 0)
        {
            point_double(R,
                         P,
                         curve);
            return;
        }

        // P = -Q -> Point at Infinity

        point_set_infinity(R);
        return;
    }

    // General Point Addition

    mpz_t lambda;
    mpz_t numerator;
    mpz_t denominator;
    mpz_t x3;
    mpz_t y3;
    mpz_t temp;

    mpz_inits(lambda,
              numerator,
              denominator,
              x3,
              y3,
              temp,
              NULL);

    // numerator = y2 - y1
    

    field_sub(numerator,
              Q->y,
              P->y,
              curve->p);

    // denominator = x2 - x1


    field_sub(denominator,
              Q->x,
              P->x,
              curve->p);

    // lambda = numerator / denominator

    if (!field_div(lambda,
                   numerator,
                   denominator,
                   curve->p))
    {
        point_set_infinity(R);

        mpz_clears(lambda,
                   numerator,
                   denominator,
                   x3,
                   y3,
                   temp,
                   NULL);

        return;
    }

    // x3 = lambda^2 - x1 - x2


    field_mul(x3,
              lambda,
              lambda,
              curve->p);

    field_sub(x3,
              x3,
              P->x,
              curve->p);

    field_sub(x3,
              x3,
              Q->x,
              curve->p);

    // y3 = lambda(x1 - x3) - y1


    field_sub(temp,
              P->x,
              x3,
              curve->p);

    field_mul(temp,
              lambda,
              temp,
              curve->p);

    field_sub(y3,
              temp,
              P->y,
              curve->p);

    // Store result


    mpz_set(R->x, x3);
    mpz_set(R->y, y3);

    R->infinity = 0;

    mpz_clears(lambda,
               numerator,
               denominator,
               x3,
               y3,
               temp,
               NULL);
}


// Compute R = P - Q
void point_subtract(ECPoint *R,
                    const ECPoint *P,
                    const ECPoint *Q,
                    const EllipticCurve *curve)
{
    ECPoint negQ;

    point_init(&negQ);

    point_negate(&negQ,
                 Q,
                 curve);

    point_add(R,
              P,
              &negQ,
              curve);

    point_clear(&negQ);
}


// Point Display
// Print a point
void point_print(const ECPoint *P)
{
    if (point_is_infinity(P))
    {
        printf("O (Point at Infinity)\n");
        return;
    }

    gmp_printf("(%Zd, %Zd)\n",
               P->x,
               P->y);
}

// Generating csv of Data Points

void export_curve_points_csv(const EllipticCurve *curve,
                             const char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        fprintf(stderr, "Error: Cannot create %s\n", filename);
        return;
    }

    fprintf(fp, "x,y\n");

    ECPoint P;

    point_init(&P);

    for (unsigned long x = 0; x < mpz_get_ui(curve->p); x++)
    {
        mpz_set_ui(P.x, x);

        for (unsigned long y = 0; y < mpz_get_ui(curve->p); y++)
        {
            mpz_set_ui(P.y, y);

            P.infinity = 0;

            if (point_is_on_curve(&P, curve))
            {
                fprintf(fp, "%lu,%lu\n", x, y);
            }
        }
    }

    point_clear(&P);

    fclose(fp);

    printf("Curve points exported to %s\n", filename);
}