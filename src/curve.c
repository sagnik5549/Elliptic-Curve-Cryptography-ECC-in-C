#include <stdio.h>

#include <gmp.h>

#include "curve.h"
#include "config.h"


// Initialize curve parameters
void curve_init(EllipticCurve *curve)
{
    mpz_init(curve->p);
    mpz_init(curve->a);
    mpz_init(curve->b);

    mpz_init(curve->gx);
    mpz_init(curve->gy);

    mpz_init(curve->n);

    mpz_set_str(curve->p, CURVE_P, 10);
    mpz_set_str(curve->a, CURVE_A, 10);
    mpz_set_str(curve->b, CURVE_B, 10);

    mpz_set_str(curve->gx, GENERATOR_X, 10);
    mpz_set_str(curve->gy, GENERATOR_Y, 10);

    mpz_set_ui(curve->n, 0);
}


// Release allocated GMP memory
void curve_clear(EllipticCurve *curve)
{
    mpz_clear(curve->p);
    mpz_clear(curve->a);
    mpz_clear(curve->b);

    mpz_clear(curve->gx);
    mpz_clear(curve->gy);

    mpz_clear(curve->n);
}


// Display curve parameters
void curve_print(const EllipticCurve *curve)
{
    printf("\n\t\tElliptic Curve Parameters \n");

    printf("Curve Name          : %s\n", CURVE_NAME);

    gmp_printf("Prime (p)           : %Zd\n", curve->p);
    gmp_printf("Coefficient (a)     : %Zd\n", curve->a);
    gmp_printf("Coefficient (b)     : %Zd\n", curve->b);

    gmp_printf("Generator G         : (%Zd, %Zd)\n",
               curve->gx,
               curve->gy);

    if (mpz_cmp_ui(curve->n, 0) == 0)
    {
        printf("Generator Order (n) : Not Set\n");
    }
    else
    {
        gmp_printf("Generator Order (n) : %Zd\n", curve->n);
    }

    gmp_printf("\nEquation            : y^2 = x^3 + %Zdx + %Zd (mod %Zd)\n",
               curve->a,
               curve->b,
               curve->p);
}