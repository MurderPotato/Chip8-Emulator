#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "chip8.h"

void executeInstruction(uint32_t buffer[64 * 32], Chip8 *values)
{
  if ((values->opcode & 0xF000) == 0x0000)
  {
    if (values->opcode == 0x00E0)
    {
      for (int i = 0; i < 64 * 32; i++)
      {
        buffer[i] = 0x00000000;
      }
    }
    else if (values->opcode == 0x00EE)
    {
      values->PC = values->stack[values->SP];
      values->SP--;
    }
  }
  else if ((values->opcode & 0xF000) == 0x1000)
  {
    values->PC = (values->opcode & 0x0FFF);
  }
  else if ((values->opcode & 0xF000) == 0x2000)
  {
    values->SP++;
    values->stack[values->SP] = values->PC;
    values->PC = (values->opcode & 0x0FFF);
  }
  else if ((values->opcode & 0xF000) == 0x3000)
  {
    int x = ((values->opcode & 0x0F00) >> 8);
    if (values->V[x] == (values->opcode & 0x00FF))
    {
      values->PC += 2;
    }
  }
  else if ((values->opcode & 0xF000) == 0x4000)
  {
    int x = ((values->opcode & 0x0F00) >> 8);
    if (values->V[x] != (values->opcode & 0x00FF))
    {
      values->PC += 2;
    }
  }
  else if ((values->opcode & 0xF00F) == 0x5000)
  {
    int x = ((values->opcode & 0x0F00) >> 8);
    int y = ((values->opcode & 0x00F0) >> 4);
    if (values->V[x] == values->V[y])
    {
      values->PC += 2;
    }
  }
  else if ((values->opcode & 0xF000) == 0x6000)
  {
    int x = ((values->opcode & 0x0F00) >> 8);
    values->V[x] = (values->opcode & 0x00FF);
  }
  else if ((values->opcode & 0xF000) == 0x7000)
  {
    int x = ((values->opcode & 0x0F00) >> 8);
    values->V[x] += (values->opcode & 0x00FF);
  }
  else if ((values->opcode & 0xF000) == 0x8000)
  {
    if ((values->opcode & 0xF00F) == 0x8000)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int y = ((values->opcode & 0x00F0) >> 4);
      values->V[x] = values->V[y];
    }
    else if ((values->opcode & 0xF00F) == 0x8001)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int y = ((values->opcode & 0x00F0) >> 4);
      values->V[x] = (values->V[x] | values->V[y]);
    }
    else if ((values->opcode & 0xF00F) == 0x8002)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int y = ((values->opcode & 0x00F0) >> 4);
      values->V[x] = (values->V[x] & values->V[y]);
    }
    else if ((values->opcode & 0xF00F) == 0x8003)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int y = ((values->opcode & 0x00F0) >> 4);
      values->V[x] = (values->V[x] ^ values->V[y]);
    }
    else if ((values->opcode & 0xF00F) == 0x8004)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int y = ((values->opcode & 0x00F0) >> 4);
      int val = values->V[x];
      values->V[x] = (values->V[x] + values->V[y]);
      if (values->V[x] < val)
      {
        values->V[15] = 1;
      }
      else
      {
        values->V[15] = 0;
      }
    }
    else if ((values->opcode & 0xF00F) == 0x8005)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int y = ((values->opcode & 0x00F0) >> 4);
      if (values->V[x] > values->V[y])
      {
        values->V[15] = 1;
      }
      else
      {
        values->V[15] = 0;
      }
      values->V[x] = (values->V[x] - values->V[y]);
    }
    else if ((values->opcode & 0xF00F) == 0x8006)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      if ((values->V[x] & 0x01) == 0x01)
      {
        values->V[15] = 1;
      }
      else
      {
        values->V[15] = 0;
      }
      values->V[x] >>= 1;
    }
    else if ((values->opcode & 0xF00F) == 0x8007)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int y = ((values->opcode & 0x00F0) >> 4);
      if (values->V[y] > values->V[x])
      {
        values->V[15] = 1;
      }
      else
      {
        values->V[15] = 0;
      }
      values->V[x] = (values->V[y] - values->V[x]);
    }
    else if ((values->opcode & 0xF00F) == 0x800E)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      if ((values->V[x] & 0x80) == 0x80)
      {
        values->V[15] = 1;
      }
      else
      {
        values->V[15] = 0;
      }
      values->V[x] <<= 1;
    }
  }
  else if ((values->opcode & 0xF00F) == 0x9000)
  {
    int x = ((values->opcode & 0x0F00) >> 8);
    int y = ((values->opcode & 0x00F0) >> 4);
    if (values->V[x] != values->V[y])
    {
      values->PC += 2;
    }
  }
  else if ((values->opcode & 0xF000) == 0xA000)
  {
    values->I = (values->opcode & 0x0FFF);
  }
  else if ((values->opcode & 0xF000) == 0xB000)
  {
    values->PC = (values->opcode & 0x0FFF) + values->V[0];
  }
  else if ((values->opcode & 0xF000) == 0xC000)
  {
    int x = ((values->opcode & 0x0F00) >> 8);
    int random = rand() % 256;
    values->V[x] = (random & (values->opcode & 0x00FF));
  }
  else if ((values->opcode & 0xF000) == 0xD000)
  {
    int xcoord = values->V[((values->opcode & 0x0F00) >> 8)];
    int ycoord = values->V[((values->opcode & 0x00F0) >> 4)];
    int n = (values->opcode & 0x000F);
    values->V[15] = 0;
    for (int i = 0; i < n; i++)
    {
      uint8_t byte = values->RAM[values->I + i];
      for (int j = 0; j < 8; j++)
      {
        int x = (xcoord + j) % 64;
        int y = (ycoord + i) % 32;
        int index = x + y * 64;
        uint8_t color = byte & 0x80;
        byte <<= 1;
        if (color == 0x80)
        {
          if (buffer[index] != 0x00000000)
          {
            values->V[15] = 1;
          }
          buffer[index] ^= 0xFFFFFFFF;
        }
      }
    }
  }
  else if ((values->opcode & 0xF000) == 0xE000)
  {
    if ((values->opcode & 0xF0FF) == 0xE09E)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int index = (values->V[x] & 0xF);
      if (values->keys[index] == true)
      {
        values->PC += 2;
      }
    }
    else if ((values->opcode & 0xF0FF) == 0xE0A1)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int index = (values->V[x] & 0xF);
      if (values->keys[index] == false)
      {
        values->PC += 2;
      }
    }
  }
  else if ((values->opcode & 0xF000) == 0xF000)
  {
    if ((values->opcode & 0xF0FF) == 0xF007)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      values->V[x] = values->DT;
    }
    else if ((values->opcode & 0xF0FF) == 0xF00A)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      values->interrupt = true;
      values->interruptReg = x;
    }
    else if ((values->opcode & 0xF0FF) == 0xF015)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      values->DT = values->V[x];
    }
    else if ((values->opcode & 0xF0FF) == 0xF018)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      values->ST = values->V[x];
    }
    else if ((values->opcode & 0xF0FF) == 0xF01E)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      values->I = (values->I + values->V[x]);
    }
    else if ((values->opcode & 0xF0FF) == 0xF029)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      int sprite = values->V[x] & 0xF;
      values->I = 5 * sprite;
    }
    else if ((values->opcode & 0xF0FF) == 0xF033)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      values->RAM[values->I] = values->V[x] / 100;
      values->RAM[values->I + 1] = values->V[x] % 100 / 10;
      values->RAM[values->I + 2] = values->V[x] % 100 % 10;
    }
    else if ((values->opcode & 0xF0FF) == 0xF055)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      for (int i = 0; i <= x; i++)
      {
        values->RAM[values->I + i] = values->V[i];
      }
    }
    else if ((values->opcode & 0xF0FF) == 0xF065)
    {
      int x = ((values->opcode & 0x0F00) >> 8);
      for (int i = 0; i <= x; i++)
      {
        values->V[i] = values->RAM[values->I + i];
      }
    }
  }
}

void handleKeypress(Chip8 *values, int keycode, bool pressed)
{
  // the four leftmost columns of keys are the ones used
  // so 1234, qwer, asdf, zxcv. this just maps them to an array
  int index;
  switch (keycode)
  {
  case 49: // 1
    index = 1;
    break;
  case 50: // 2
    index = 2;
    break;
  case 51: // 3
    index = 3;
    break;
  case 52: // 4
    index = 0xC;
    break;
  case 113: // q
    index = 4;
    break;
  case 119: // w
    index = 5;
    break;
  case 101: // e
    index = 6;
    break;
  case 114: // r
    index = 0xD;
    break;
  case 97: // a
    index = 7;
    break;
  case 115: // s
    index = 8;
    break;
  case 100: // d
    index = 9;
    break;
  case 102: // f
    index = 0xE;
    break;
  case 122: // z
    index = 0xA;
    break;
  case 120: // x
    index = 0;
    break;
  case 99: // c
    index = 0xB;
    break;
  case 118: // v
    index = 0xF;
    break;
  }
  if (pressed == true)
  {
    if (values->interrupt == true)
    {
      values->V[values->interruptReg] = index;
      values->interrupt = false;
    }
    values->keys[index] = true;
  }
  else
  {
    values->keys[index] = false;
  }
}