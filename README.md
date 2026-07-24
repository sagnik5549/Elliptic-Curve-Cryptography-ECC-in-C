# Elliptic Curve Cryptography (ECC) in C

A modular implementation of **Elliptic Curve Cryptography (ECC)** in C using the **GNU Multiple Precision Arithmetic Library (GMP)**. The project demonstrates the mathematical foundations of ECC, including finite field arithmetic, elliptic curve point operations, key generation, Elliptic Curve Diffie-Hellman (ECDH), message encoding, encryption, and curve visualization.

## Features

- Finite field arithmetic
- Elliptic curve point addition and doubling
- Scalar multiplication (Double-and-Add)
- ECC key generation
- Elliptic Curve Diffie-Hellman (ECDH)
- Message encoding
- ECC encryption and decryption
- Curve point export to CSV
- Python-based curve visualization

## Project Structure

```
ECC-with-only-C/
│
├── include/
│   ├── config.h
│   ├── curve.h
│   ├── ecdh.h
│   ├── encode.h
│   ├── encryption.h
│   ├── field.h
│   ├── keygen.h
│   ├── point.h
│   └── scalar.h
│
├── src/
│   ├── curve.c
│   ├── ecdh.c
│   ├── encode.c
│   ├── encryption.c
│   ├── field.c
│   ├── keygen.c
│   ├── point.c
│   ├── scalar.c
│   └── main.c
│
├── graph.py
├── curve_points.csv
├── ecc_curve_plot.png
├── Makefile
├── requirements.md
├── .gitignore
└── README.md
```

## Modules

| Module | Purpose |
|---------|---------|
| `field` | Finite field arithmetic |
| `point` | Point representation and utilities |
| `curve` | Point addition and doubling |
| `scalar` | Scalar multiplication |
| `keygen` | Public/private key generation |
| `ecdh` | Shared secret generation |
| `encode` | Message encoding |
| `encryption` | ECC encryption and decryption |
| `graph.py` | Curve visualization |

## Workflow

```
Initialize Curve
      ↓
Generate Curve Points
      ↓
Generate Key Pair
      ↓
Encode Message
      ↓
Encrypt Message
      ↓
ECDH Key Exchange
      ↓
Decrypt Message
      ↓
Export CSV & Plot Curve
```

## Output

- `curve_points.csv` — Generated curve points
- `ecc_curve_plot.png` — Curve visualization
- `ecc.exe` — Compiled executable

## Requirements

See **requirements.md** for software dependencies and libraries.

## Author

**Sagnik Kundu**  
B.Tech Computer Science and Engineering (AI & DS)
SASTRA Deemed University