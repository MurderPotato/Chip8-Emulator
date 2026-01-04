#include <SDL3/SDL.h>

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "chip8.h"

void initializeSprites(Chip8 *values) // Adds the base hex values to the sprite table
{
  uint8_t Chip8Font[80] = {
      0xF0, 0x90, 0x90, 0x90, 0xF0,
      0x20, 0x60, 0x20, 0x20, 0x70,
      0xF0, 0x10, 0xF0, 0x80, 0xF0,
      0xF0, 0x10, 0xF0, 0x10, 0xF0,
      0x90, 0x90, 0xF0, 0x10, 0x10,
      0xF0, 0x80, 0xF0, 0x10, 0xF0,
      0xF0, 0x80, 0xF0, 0x90, 0xF0,
      0xF0, 0x10, 0x20, 0x40, 0x40,
      0xF0, 0x90, 0xF0, 0x90, 0xF0,
      0xF0, 0x90, 0xF0, 0x10, 0xF0,
      0xF0, 0x90, 0xF0, 0x90, 0x90,
      0xE0, 0x90, 0xE0, 0x90, 0xE0,
      0xF0, 0x80, 0x80, 0x80, 0xF0,
      0xE0, 0x90, 0x90, 0x90, 0xE0,
      0xF0, 0x80, 0xF0, 0x80, 0xF0,
      0xF0, 0x80, 0xF0, 0x80, 0x80};

  for (int i = 0; i < (5 * 16); i++)
  {
    values->RAM[i] = Chip8Font[i];
  }
}

void initializeValues(Chip8 *values) // zeroes registers and memory
{
  // Registers
  memset(&values->V, 0, sizeof(values->V));
  values->I = 0;
  values->DT = 0;
  values->ST = 0;
  values->PC = 256;
  values->SP = 0;
  // Memory
  memset(&values->RAM, 0, sizeof(values->RAM));
  memset(&values->stack, 0, sizeof(values->stack));
  memset(&values->keys, false, sizeof(values->keys));
  // Current Instruction
  values->opcode = 0;
  values->interrupt = false;
}

int loadROM(const char *filename, Chip8 *values) // loads file into RAM
{
  FILE *file = fopen(filename, "rb");
  if (!file)
  {
    SDL_Log("File Failed to Open");
    return 1;
  }
  int c;
  uint16_t counter = 0x200;
  while ((c = fgetc(file)) != EOF)
  {
    values->RAM[counter] = c;
    counter++;
  }
  if (feof(file))
  {
    SDL_Log("ROM Loaded Sucessfully");
    return 0;
  }
  return 1;
}