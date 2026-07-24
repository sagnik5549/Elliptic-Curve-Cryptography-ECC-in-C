#ifndef ENCODE_H
#define ENCODE_H

#include <gmp.h>

#include "curve.h"
#include "point.h"
#include "field.h"

/*
 * Message Encoding
 *
 * This module implements a deterministic
 * Try-and-Increment algorithm for mapping
 * plaintext characters onto elliptic curve
 * points.
 *
 * Encoding
 * --------
 * Character --> EC Point + Offset
 *
 * Decoding
 * --------
 * EC Point + Offset --> Character
 */


/*
 * Encode a single character into an
 * elliptic curve point.
 *
 * Parameters:
 *      encoded_point : Output EC point.
 *      offset        : Number of increments used.
 *      character     : Plaintext character.
 *      curve         : Elliptic curve.
 *
 * Returns:
 *      1 on success.
 *      0 on failure.
 */

int encode_character(ECPoint *encoded_point,
                     unsigned int *offset,
                     unsigned char character,
                     const EllipticCurve *curve);


/*
 * Decode an encoded point back into
 * the original character.
 */

unsigned char decode_character(const ECPoint *encoded_point,
                               unsigned int offset);

#endif