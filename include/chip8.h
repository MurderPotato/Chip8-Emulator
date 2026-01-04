#pragma once

#include <stdint.h>

typedef struct
{
  // Registers
  uint8_t V[16]; // general purpose registers
  uint16_t I;    // memory address register
  uint8_t DT;    // delay timer register
  uint8_t ST;    // sound timer register
  uint16_t PC;   // program counter
  uint8_t SP;    // stack pointer

  // memory
  uint8_t RAM[4096];
  uint16_t stack[16];
  bool keys[16];

  // current instruction
  uint16_t opcode;

  // keyboard interrupts
  bool interrupt;
  uint8_t interruptReg;

} Chip8;
