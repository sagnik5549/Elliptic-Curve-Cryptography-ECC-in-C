#ifndef CURVE_H
#define CURVE_H

#include <gmp.h>

/*
 * Represents an elliptic curve over a prime finite field.
 *
 * Curve Equation:
 *      y² = x³ + ax + b (mod p)
 */
typedef struct
{
    mpz_t p;      // Prime modulus
    mpz_t a;      // Curve coefficient
    mpz_t b;      // Curve coefficient

    mpz_t gx;     // Generator point x-coordinate
    mpz_t gy;     // Generator point y-coordinate

    mpz_t n;      // Order of the generator (set at runtime)

} EllipticCurve;


// Curve management

void curve_init(EllipticCurve *curve);

void curve_clear(EllipticCurve *curve);


// Display 

void curve_print(const EllipticCurve *curve);

#endif