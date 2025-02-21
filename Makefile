all: space_invaders.o player_obj.o
	@gcc space_invaders.o player_obj.o -o space_invaders -Wall -lSDL2 -lSDL2_image -lSDL2_ttf
	@rm *.o 


space_invaders.o: include/space_invaders.h
	@gcc -c space_invaders.c

player_obj.o: include/objects.h include/player_obj.h
	@gcc -c player_obj.c

run: space_invaders.o player_obj.o
	@gcc space_invaders.o player_obj.o -o space_invaders -Wall -lSDL2 -lSDL2_image -lSDL2_ttf
	@./space_invaders
	@rm *.o space_invaders

