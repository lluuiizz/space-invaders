#include "include/space_invaders.h"
#include "include/player_obj.h"
#include <stdlib.h>

int main(void) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Erro ao inicializar o SDL2: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		printf("Erro ao criar janela: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (render == NULL) {
		printf("Erro ao criar render: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	bool running = true;
	SDL_Event event;

	Objects *game_objects = (Objects*) malloc(sizeof(Objects));
	Objects *player_obj   = (Objects*) malloc(sizeof(Objects));

	game_objects = player_obj;

	initialize_player_state(render, player_obj);

	while (running){
		SDL_SetRenderDrawColor(render, 80, 243, 144, 255);
		while(SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
		SDL_RenderClear(render);

		render_player_current_state(render, player_obj);
		SDL_RenderPresent(render);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();


	return 0;



}
