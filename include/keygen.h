#ifndef KEYGEN_H
#define KEYGEN_H

#include <gmp.h>

#include "curve.h"
#include "point.h"
#include "scalar.h"

/*
 * ECC Key Pair
 *
 * Private Key : d
 * Public Key  : Q = d × G
 */

typedef struct
{
    mpz_t private_key;
    ECPoint public_key;

} ECCKeyPair;


/* Key Management */

void keypair_init(ECCKeyPair *keypair);

void keypair_clear(ECCKeyPair *keypair);


/* Key Generation */

void generate_keypair(ECCKeyPair *keypair,
                      const EllipticCurve *curve);


/* Display */

void keypair_print(const ECCKeyPair *keypair);

#endif