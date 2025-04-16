#include "include/bullet.h"
#include "include/space_invaders.h"
#include "include/player.h"
#include "include/objects.h"
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

	Object player;
	Objects enemys = (Objects) malloc(sizeof(Object) * 10);
	Objects *all_objects = (Objects*) malloc(sizeof(Object) * 2); // Esse tipo de vetor será utilizado para renderizar todos 
	Bullet_list *bullet_list = initialize_bullet_list();
	all_objects[Player] = &player;														      // Os elementos diferentes do jogo. 
	all_objects[Enemy] = enemys;																						   



	initialize_player_state(render, &player);


	while (running){
		SDL_SetRenderDrawColor(render, 80, 243, 144, 255);
		SDL_RenderClear(render);

		while(SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		actualize_player_current_state(render, bullet_list, &player);
		render_game_objects(render, bullet_list, all_objects);
		
		SDL_Delay(TICKS_PER_FRAME);
		SDL_RenderPresent(render);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();




	return 0;

}


void render_game_objects (SDL_Renderer *render, Bullet_list *bullet_list, Objects* all_game_objects){
	Object_type different_objects[] = {Player, Enemy, Bullet};
	int each = 0;
	do{

		if (different_objects[each] == Player){
			render_player_current_state(render, all_game_objects[Player]);
		}
		else if (different_objects[each] == Enemy){
			SDL_Log("Here we send the enemy to render\n");
		}
		else if (different_objects[each] == Bullet){
			SDL_Log("Here we send the BULLETS to render\n");
			Bullet_obj *aux = bullet_list->head;

			for (int i = 0; i < bullet_list->nbullets; i++){
				SDL_Log("Rendering bullet %d out of %d\n",i+1, bullet_list->nbullets);
				SDL_Rect crop_sprite = {0, 0, BULLET_W, BULLET_H};
				SDL_RenderCopy(render, aux->render_info.sprite, &crop_sprite, &(aux->render_info).collision );
				aux = aux->prox;
			}
			
		}

		each++;
	} while (each != NUM_OF_DIFFERENT_OBJECTS);

}
