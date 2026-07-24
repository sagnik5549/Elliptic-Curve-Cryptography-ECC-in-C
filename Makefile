CC = gcc

CFLAGS = -Wall -Wextra -O2 -Iinclude

LDFLAGS = -lgmp

TARGET = ecc_demo.exe

SRC = \
	src/main.c \
	src/curve.c \
	src/field.c \
	src/point.c \
	src/scalar.c \
	src/keygen.c \
	src/ecdh.c \
	src/encode.c \
	src/encryption.c

OBJ = $(SRC:.c=.o)


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f src/*.o
	rm -f $(TARGET)

rebuild: clean all

.PHONY: all run clean rebuild