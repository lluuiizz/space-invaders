all: space_invaders.o
	@gcc space_invaders.o -o space_invaders -Wall -lSDL2 -lSDL2_image -lSDL2_ttf
	@rm space_invaders.o 


space_invaders.o: include/space_invaders.h
	@gcc -c space_invaders.c

run: space_invaders.o
	@gcc space_invaders.o -o space_invaders -Wall -lSDL2 -lSDL2_image -lSDL2_ttf
	@./space_invaders
	@rm space_invaders.o space_invaders

