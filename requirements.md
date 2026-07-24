# Project Requirements

## Compiler

- GCC / MinGW GCC (C17 compatible)

## Build Tool

- GNU Make

## C Library

- GNU Multiple Precision Arithmetic Library (GMP)

## Python

- Python 3.x

### Python Packages

- pandas
- matplotlib
- numpy
- scipy

## Operating Systems

- Windows (MinGW/MSYS2)
- Linux

## Project Structure

Required files and directories:

- include/
- src/
- output/
- graphs/
- graph.py
- Makefile

## Generated Files

### Output Data

- output/curve_points.csv
- output/plain_points.csv
- output/cipher_points.csv

### Generated Graphs

- graphs/ecc_curve_plot.png
- graphs/plain_points_plot.png
- graphs/cipher_points_plot.png

### Executable

- ecc.exe (Windows)
- ecc (Linux)