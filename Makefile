CC=gcc

EXT_INC= -I external/include
EXT_LIB= -L external/lib
SDL_DLL= -lSDL3

CFLAGS= -Wall -Wextra -pedantic
INC= -I include

OFILES= chip8.o core.o init.o

chip8: chip8.o core.o init.o
	$(CC) $(CFLAGS) $(OFILES) $(EXT_LIB) $(SDL_DLL) -o chip8

chip8.o: src/chip8.c include/chip8.h
	$(CC) $(CFLAGS) $(EXT_INC) $(INC) -c src/chip8.c

core.o: src/core.c include/core.h
	$(CC) $(CFLAGS) $(EXT_INC) $(INC) -c src/core.c

init.o: src/init.c include/init.h
	$(CC) $(CFLAGS) $(EXT_INC) $(INC) -c src/init.c

clean:
	rm -f *.o test