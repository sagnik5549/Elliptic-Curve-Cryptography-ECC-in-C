#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <gmp.h>

#include "keygen.h"

// Key Management

// Initialize an ECC key pair
void keypair_init(ECCKeyPair *keypair)
{
    mpz_init(keypair->private_key);

    point_init(&keypair->public_key);
}


// Release allocated memory
void keypair_clear(ECCKeyPair *keypair)
{
    mpz_clear(keypair->private_key);

    point_clear(&keypair->public_key);
}

// Generate an ECC key pair
void generate_keypair(ECCKeyPair *keypair,
                      const EllipticCurve *curve)
{

    gmp_randstate_t state;

    gmp_randinit_default(state);

    /*
     * Seed using both current time and CPU clock
     * to reduce the chance of identical seeds.
     */

    unsigned long seed =
        (unsigned long)time(NULL) ^
        (unsigned long)clock() ^
        (unsigned long)rand();

    gmp_randseed_ui(state, seed);

    ECPoint G;

    point_init(&G);

    point_set(&G,
          curve->gx,
          curve->gy);

    if (!point_is_on_curve(&G, curve))
    {
        fprintf(stderr, "Error: Generator point is not on the curve.\n");

        gmp_randclear(state);
        return;
    }

    /*
     * Generate:
     *
     *      1 <= private_key < p
     *
     * Normally ECC uses:
     *
     *      1 <= private_key < n
     *
     * where n is the order of the generator point.
     *
     * This project does not define n, so p is used
     * as the upper bound.
     */
 
    do
    {
        mpz_urandomm(keypair->private_key,
                     state,
                     curve->p);

    } while (mpz_cmp_ui(keypair->private_key, 0) == 0);

    /*
     * Compute the public key:
     *
     *      Q = d × G
     */

    scalar_multiply(&keypair->public_key,
                    keypair->private_key,
                    &G,
                    curve);
    point_clear(&G);

    gmp_randclear(state);
}

// Display an ECC key pair
void keypair_print(const ECCKeyPair *keypair)
{
    if (keypair == NULL)
    {
        fprintf(stderr, "Error: Invalid key pair.\n");
        return;
    }

    gmp_printf("Private Key : %Zd\n",
               keypair->private_key);

    printf("Public Key  : ");

    point_print(&keypair->public_key);
}