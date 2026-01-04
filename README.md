# Chip8 Emulator

This is my implementation of the Chip8 written in C and using SDL3 for the graphics.
It was designed to be compiled and ran on windows but should run on linux as well.

## Build Instructions

1. Download the SDL3 Library 

SDL3-devel-3.4.0-mingw.zip from https://github.com/libsdl-org/SDL/releases/tag/release-3.4.0

2. Add files to project

* Create a folder called external in the main directory
* Copy .\SDL3-3.2.28\x86_64-w64-mingw32\include to the include folder
* Copy .\SDL3-3.2.28\x86_64-w64-mingw32\lib to the lib folder
* Copy \SDL3-3.2.28\x86_64-w64-mingw32\bin\SDL3.dll to the main project directory
* Run make through MinGW

Once the executable is Built, you can run any ROM from the ROMS folder using this command:
```
./chip8.exe foo.ch8 #OfCyclesPerFrame
```

### Example Images

![Test rom](/images/Test.png)

![Sirpinsky Triangle](/images/Sirpinsky.png)

![Breakout](/images/Breakout.png)
