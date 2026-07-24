#include <stdio.h>
#include <stdlib.h>

#include <gmp.h>

#include "ecdh.h"

/*
 * Compute the ECDH shared secret.
 *
 *      S = d × Q
 *
 * where:
 *      d = private key
 *      Q = other party's public key
 */
void compute_shared_secret(ECPoint *shared_secret,
                           const mpz_t private_key,
                           const ECPoint *public_key,
                           const EllipticCurve *curve)
{
    if (shared_secret == NULL ||
        public_key == NULL ||
        curve == NULL)
    {
        fprintf(stderr, "Error: Invalid argument passed to compute_shared_secret().\n");
        return;
    }

    if (!point_is_on_curve(public_key, curve))
    {
        fprintf(stderr, "Error: Public key is not on the curve.\n");

        point_set_infinity(shared_secret);
        return;
    }

    scalar_multiply(shared_secret,
                    private_key,
                    public_key,
                    curve);
}