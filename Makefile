all: space_invaders.o player_obj.o 
	@gcc space_invaders.o player_obj.o -o space_invaders -Wall -lSDL2 -lSDL2_image -lSDL2_ttf
	@rm *.o 

run: space_invaders.o player_obj.o 
	@gcc space_invaders.o player_obj.o -o space_invaders -Wall -lSDL2 -lSDL2_image -lSDL2_ttf
	@./space_invaders
	@rm *.o space_invaders

space_invaders.o:
	@gcc -c space_invaders.c

player_obj.o: 
	@gcc -c player_obj.c



