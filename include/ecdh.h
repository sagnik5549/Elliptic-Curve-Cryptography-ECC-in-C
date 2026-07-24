#ifndef ECDH_H
#define ECDH_H

#include <gmp.h>

#include "curve.h"
#include "point.h"
#include "scalar.h"
#include "keygen.h"

/*
 * Elliptic Curve Diffie-Hellman (ECDH)
 *
 * Computes a shared secret using:
 *
 *      S = d × Q
 *
 * where:
 *      d = private key
 *      Q = other party's public key
 *
 * Alice computes:
 *
 *      S = dA × QB
 *
 * Bob computes:
 *
 *      S = dB × QA
 *
 * Both obtain the same shared secret.
 */

void compute_shared_secret(ECPoint *shared_secret,
                           const mpz_t private_key,
                           const ECPoint *public_key,
                           const EllipticCurve *curve);

#endif