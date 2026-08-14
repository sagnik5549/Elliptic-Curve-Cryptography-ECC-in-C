#ifndef CONFIG_H
#define CONFIG_H

/* Elliptic Curve Parameters
 *
 * Curve Equation:
 *      y² = x³ + ax + b (mod p)
 *
 * This configuration uses the small example curve from
 * Stallings' Cryptography and Network Security textbook.
 */   

#define CURVE_NAME "ECC Curve"

#define CURVE_P      "211"
#define CURVE_A      "0"
#define CURVE_B      "-4"

#define GENERATOR_X  "2"
#define GENERATOR_Y  "2"


#endif