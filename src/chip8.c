#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_render.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "chip8.h"
#include "init.h"
#include "core.h"

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("Invalid arguments. Include: exe, ___.ch8, cycle-rate (int)");
    printf("Make sure to have ROMS folder in the same directory as the exe");
    return 1;
  }

  srand(time(NULL));

  // creating chip8 structure and initializing values
  Chip8 chip8;
  initializeValues(&chip8);
  initializeSprites(&chip8);
  if (loadROM(argv[1], &chip8) == 1)
  {
    return 1;
  }

  int width = 64;
  int height = 32;
  int scale = 10;

  uint32_t buffer[64 * 32] = {0};

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow(argv[1], width * scale, height * scale, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, "opengl");
  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_EVENT_QUIT:
        running = false;
        break;
      case SDL_EVENT_KEY_DOWN:
        handleKeypress(&chip8, event.key.key, true);
        break;
      case SDL_EVENT_KEY_UP:
        handleKeypress(&chip8, event.key.key, false);
        break;
      default:
        break;
      }
    }
    // Emulator Loop
    if (chip8.interrupt == false)
    {
      for (int i = 0; i < atoi(argv[2]); i++)
      {
        uint16_t highByte = chip8.RAM[chip8.PC];
        uint16_t lowByte = chip8.RAM[chip8.PC + 1];
        uint16_t opcode = (highByte << 8) + lowByte;

        chip8.PC += 2;
        chip8.opcode = opcode;

        executeInstruction(buffer, &chip8);
        if (chip8.interrupt == true)
        {
          break;
        }
      }
    }

    Sleep(5);
    SDL_UpdateTexture(texture, NULL, &buffer, width * sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_Quit();

  return 0;
}