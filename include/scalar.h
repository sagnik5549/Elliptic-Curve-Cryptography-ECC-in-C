#ifndef SCALAR_H
#define SCALAR_H

#include <gmp.h>

#include "curve.h"
#include "point.h"

/*
 * Scalar Multiplication
 *
 * Computes:
 *      R = k × P
 *
 * where
 *      k : scalar (private key)
 *      P : elliptic curve point
 *      R : resulting point
 */

void scalar_multiply(ECPoint *R,
                     const mpz_t k,
                     const ECPoint *P,
                     const EllipticCurve *curve);

#endif