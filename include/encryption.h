#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <gmp.h>

#include "curve.h"
#include "point.h"
#include "scalar.h"
#include "field.h"

/*
 * Elliptic Curve ElGamal Encryption
 *
 * Encryption:
 *
 *      C1 = kG
 *      C2 = Pm + kPB
 *
 * Ciphertext:
 *
 *      C = (C1, C2)
 *
 * Decryption:
 *
 *      Pm = C2 − nB(C1)
 */

typedef struct
{
    ECPoint C1;
    ECPoint C2;

} ECCCiphertext;


/* Ciphertext Management */

void ciphertext_init(ECCCiphertext *cipher);

void ciphertext_clear(ECCCiphertext *cipher);


/* Encryption */

int encrypt_point(ECCCiphertext *cipher,
                  const ECPoint *message,
                  const ECPoint *receiver_public_key,
                  const EllipticCurve *curve);


/* Decryption */

int decrypt_point(ECPoint *message,
                  const ECCCiphertext *cipher,
                  const mpz_t receiver_private_key,
                  const EllipticCurve *curve);


/* Display */

void ciphertext_print(const ECCCiphertext *cipher);

#endif