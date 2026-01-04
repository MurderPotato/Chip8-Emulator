#pragma once

#include "chip8.h"

void initializeSprites(Chip8 *values); // Adds the base hex values to the sprite table

void initializeValues(Chip8 *values); // zeroes registers and memory

int loadROM(const char *filename, Chip8 *values); // loads file into RAM