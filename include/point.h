#ifndef POINT_H
#define POINT_H

#include <gmp.h>
#include "curve.h"

/*
 * Represents a point on an elliptic curve.
 *
 * If infinity == 1, the point represents
 * the point at infinity.
 */
  
typedef struct
{
    mpz_t x;
    mpz_t y;

    int infinity;

} ECPoint;


// Point management  

void point_init(ECPoint *P);

void point_clear(ECPoint *P);

void point_copy(ECPoint *dest,
                const ECPoint *src);

void point_set(ECPoint *P,
               const mpz_t x,
               const mpz_t y);


// Point state  

void point_set_infinity(ECPoint *P);

int point_is_infinity(const ECPoint *P);


// Point comparison  

int point_equal(const ECPoint *P,
                const ECPoint *Q);


// Point validation

int point_is_on_curve(const ECPoint *P,
                      const EllipticCurve *curve);
                      
void export_curve_points_csv(const EllipticCurve *curve,
                             const char *filename);
// Point arithmetic

void point_negate(ECPoint *R,
                  const ECPoint *P,
                  const EllipticCurve *curve);

void point_double(ECPoint *R,
                  const ECPoint *P,
                  const EllipticCurve *curve);

void point_add(ECPoint *R,
               const ECPoint *P,
               const ECPoint *Q,
               const EllipticCurve *curve);

void point_subtract(ECPoint *R,
                    const ECPoint *P,
                    const ECPoint *Q,
                    const EllipticCurve *curve);

// Display  

void point_print(const ECPoint *P);

#endif