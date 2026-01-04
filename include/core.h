#pragma once

#include "chip8.h"

void executeInstruction(uint32_t buffer[64 * 32], Chip8 *values); // Executes a 16 bit instruction from memory

void handleKeypress(Chip8 *values, int keycode, bool pressed); // detect whether a key is held or unheld