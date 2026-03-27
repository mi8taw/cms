# Makefile for Lightweight C CMS with SQLite
# Target: FreeBSD ARM (Raspberry Pi, ARMv8, etc.)

# -----------------------------
# Compiler settings
# -----------------------------
CC = cc                # FreeBSD default C compiler (Clang usually)
CFLAGS = -Wall -g -O2  # -Wall: warnings, -g: debug symbols, -O2: optimization

# Libraries to link (SQLite is required)
LIBS = -lsqlite3

# Executable name
TARGET = cms

# Source files
SRC = main.c db.c

# -----------------------------
# Targets
# -----------------------------

# Default target: build executable
all:
	@echo "Compiling for FreeBSD ARM..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)
	@echo "Build complete! Run './$(TARGET)' to start the CMS."

# Run directly after build
run: all
	./$(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)
	@echo "Clean complete! Executable removed."

# Cross compile for ARM (optional)
# Example: target aarch64 FreeBSD on ARM
# CC=aarch64-unknown-freebsd-clang make
