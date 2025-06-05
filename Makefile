# Compiler and flags
CC = gcc
CFLAGS = `sdl2-config --cflags` -Wall -O2
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf

# Target binary name
TARGET = fullscreen_clock

# Source file
SRC = fullscreen_clock.c

.PHONY: all clean install

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Remove built files
clean:
	rm -f $(TARGET)

# Optional install target
install:
	install -Dm755 $(TARGET) $(HOME)/.local/bin/$(TARGET)

