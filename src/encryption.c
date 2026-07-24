#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gmp.h>

#include "encryption.h"


// Ciphertext Management

// Initialize ciphertext
void ciphertext_init(ECCCiphertext *cipher)
{
    point_init(&cipher->C1);

    point_init(&cipher->C2);
}


// Release allocated memory
void ciphertext_clear(ECCCiphertext *cipher)
{
    point_clear(&cipher->C1);

    point_clear(&cipher->C2);
}


// Encryption

// Encrypt an elliptic curve point
int encrypt_point(ECCCiphertext *cipher,
                  const ECPoint *message,
                  const ECPoint *receiver_public_key,
                  const EllipticCurve *curve)
{
    if (cipher == NULL ||
        message == NULL ||
        receiver_public_key == NULL ||
        curve == NULL)
    {
        fprintf(stderr,
                "Error: Invalid argument passed to encrypt_point().\n");
        return 0;
    }

    if (!point_is_on_curve(message, curve))
    {
        fprintf(stderr,
                "Error: Message point is not on the curve.\n");
        return 0;
    }

    if (!point_is_on_curve(receiver_public_key, curve))
    {
        fprintf(stderr,
                "Error: Receiver public key is not on the curve.\n");
        return 0;
    }

    mpz_t k;

    mpz_init(k);

    gmp_randstate_t state;

    gmp_randinit_default(state);

    unsigned long seed =
        (unsigned long)time(NULL) ^
        (unsigned long)clock() ^
        (unsigned long)rand();

    gmp_randseed_ui(state, seed);

    do
    {
        mpz_urandomm(k,
                     state,
                     curve->p);

    } while (mpz_cmp_ui(k, 0) == 0);
    // Create generator point G

    ECPoint G;

    point_init(&G);

    point_set(&G,
            curve->gx,
            curve->gy);

    // C1 = kG

    scalar_multiply(&cipher->C1,
                    k,
                    &G,
                    curve);

    // temp = kPB


    ECPoint temp;

    point_init(&temp);

    scalar_multiply(&temp,
                    k,
                    receiver_public_key,
                    curve);

    // C2 = Pm + kPB


    point_add(&cipher->C2,
              message,
              &temp,
              curve);

    point_clear(&temp);

    mpz_clear(k);

    gmp_randclear(state);

    return 1;
}


// Decryption

// Decrypt an elliptic curve point
int decrypt_point(ECPoint *message,
                  const ECCCiphertext *cipher,
                  const mpz_t receiver_private_key,
                  const EllipticCurve *curve)
{
    if (message == NULL ||
        cipher == NULL ||
        curve == NULL)
    {
        fprintf(stderr,
                "Error: Invalid argument passed to decrypt_point().\n");
        return 0;
    }

    if (!point_is_on_curve(&cipher->C1, curve) ||
        !point_is_on_curve(&cipher->C2, curve))
    {
        fprintf(stderr,
                "Error: Invalid ciphertext.\n");
        return 0;
    }

    // temp = nB(C1)

    ECPoint temp;

    point_init(&temp);

    scalar_multiply(&temp,
                    receiver_private_key,
                    &cipher->C1,
                    curve);

    // Pm = C2 − nB(C1)

    point_subtract(message,
                   &cipher->C2,
                   &temp,
                   curve);

    point_clear(&temp);

    return 1;
}


// Display 

// Print ciphertext
void ciphertext_print(const ECCCiphertext *cipher)
{
    printf("Cipher Point C1:\n");

    point_print(&cipher->C1);

    printf("Cipher Point C2:\n");

    point_print(&cipher->C2);
}