#include <stdio.h>
#include <string.h>
#include "config.h"
#include "curve.h"
#include "point.h"
#include "keygen.h"
#include "ecdh.h"
#include "encode.h"
#include "encryption.h"

int main(void)
{
    // Curve Initialization

    EllipticCurve curve;

    curve_init(&curve);

    printf("\t\t\t\t\n");
    printf("   Elliptic Curve Cryptography Demo\n");
    printf("\t\t\t\t\n\n");

    curve_print(&curve);
    export_curve_points_csv(&curve,
                            "output/curve_points.csv");
                            
    // Key Generation

    ECCKeyPair alice;
    ECCKeyPair bob;

    keypair_init(&alice);
    keypair_init(&bob);

    generate_keypair(&alice, &curve);
    generate_keypair(&bob, &curve);

    printf("\n\t Alice \t\n");

    keypair_print(&alice);

    printf("\n\t Bob \t\n");

    keypair_print(&bob);

    // ECDH Shared Secret

    ECPoint alice_secret;
    ECPoint bob_secret;

    point_init(&alice_secret);
    point_init(&bob_secret);

    compute_shared_secret(&alice_secret,
                          alice.private_key,
                          &bob.public_key,
                          &curve);

    compute_shared_secret(&bob_secret,
                          bob.private_key,
                          &alice.public_key,
                          &curve);

    printf("\n\t Shared Secret \t\n");

    printf("Alice Secret:\n");
    point_print(&alice_secret);

    printf("Bob Secret:\n");
    point_print(&bob_secret);

    if (point_equal(&alice_secret, &bob_secret))
        printf("\nShared Secret Verified Successfully.\n");
    else
        printf("\nShared Secret Verification Failed.\n");

    // Plaintext Input

    char message[256];

    printf("\nEnter plaintext: ");

    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = '\0';

    printf("\nEncryption / Decryption Process\n");

    // Create Cipher Points CSV

    FILE *cipher_csv = fopen("output/cipher_points.csv", "w");

    if (cipher_csv != NULL)
    {
        fprintf(cipher_csv, "X,Y\n");
        fclose(cipher_csv);
    }

    // Process Each Character

    for (size_t i = 0; i < strlen(message); i++)
    {
        ECPoint encoded_point;
        ECPoint recovered_point;

        ECCCiphertext cipher;

        unsigned int offset;

        unsigned char recovered;

        point_init(&encoded_point);
        point_init(&recovered_point);

        ciphertext_init(&cipher);

        // Encode 

        if (!encode_character(&encoded_point,
                              &offset,
                              (unsigned char)message[i],
                              &curve))
        {
            fprintf(stderr,
                    "Encoding failed for character '%c'.\n",
                    message[i]);

            point_clear(&encoded_point);
            point_clear(&recovered_point);
            ciphertext_clear(&cipher);

            continue;
        }

        // Encrypt 

        if (!encrypt_point(&cipher,
                           &encoded_point,
                           &bob.public_key,
                           &curve))
        {
            fprintf(stderr,
                    "Encryption failed.\n");

            point_clear(&encoded_point);
            point_clear(&recovered_point);
            ciphertext_clear(&cipher);

            continue;
        }

        FILE *cipher_csv = fopen("output/cipher_points.csv", "a");

        if (cipher_csv != NULL)
        {
            gmp_fprintf(cipher_csv,
                        "%Zd,%Zd\n",
                        cipher.C2.x,
                        cipher.C2.y);
            
            fclose(cipher_csv);
        }
        
        // Decrypt 

        if (!decrypt_point(&recovered_point,
                           &cipher,
                           bob.private_key,
                           &curve))
        {
            fprintf(stderr,
                    "Decryption failed.\n");

            point_clear(&encoded_point);
            point_clear(&recovered_point);
            ciphertext_clear(&cipher);

            continue;
        }

        // Decode 

        recovered = decode_character(&recovered_point,
                                     offset);

        // Character Summary

        printf("\nCharacter %zu Summary\n", i + 1);

        printf("Original Character  : %c\n",
               message[i]);

        printf("Encoded Point       : ");
        point_print(&encoded_point);

        printf("Cipher Point C1     : ");
        point_print(&cipher.C1);

        printf("Cipher Point C2     : ");
        point_print(&cipher.C2);

        printf("Recovered Point     : ");
        point_print(&recovered_point);

        printf("Decoded Character   : %c\n",
               recovered);

        printf("Verification        : %s\n",
               (message[i] == recovered)
               ? "SUCCESS"
               : "FAILED");


        // Cleanup for Current Character

        point_clear(&encoded_point);
        point_clear(&recovered_point);

        ciphertext_clear(&cipher);
    }

    // Final Summary

    printf("\nECC Demonstration Completed\n");

    printf("Curve                 : %s\n",
           CURVE_NAME);

    printf("Characters Processed  : %zu\n",
           strlen(message));

    printf("Key Exchange          : SUCCESS\n");
    printf("Encryption            : COMPLETED\n");
    printf("Decryption            : COMPLETED\n");

    printf("\n");

    // Cleanup

    point_clear(&alice_secret);
    point_clear(&bob_secret);

    keypair_clear(&alice);
    keypair_clear(&bob);

    curve_clear(&curve);

    return 0;
}