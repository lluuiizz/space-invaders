all: space_invaders.o player.o bullet.o 
	@gcc *.o -o space_invaders -Werror -Wall -Wextra -pedantic -lSDL2 -lSDL2_image -lSDL2_ttf
	@rm *.o 

run: space_invaders.o player.o bullet.o 
	@gcc *.o -o space_invaders -Werror -Wall -Wextra -pedantic -lSDL2 -lSDL2_image -lSDL2_ttf
	@./space_invaders
	@rm *.o 

space_invaders.o:
	@gcc -c space_invaders.c
player.o: 
	@gcc -c player.c
bullet.o:
	@gcc -c bullet.c


