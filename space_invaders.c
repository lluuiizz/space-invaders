#include "include/bullet.h"
#include "include/space_invaders.h"
#include "include/player.h"
#include "include/objects.h"
#include "include/game_state.h"
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

	player_t player;
	bullet_list_t *bullet_list = initialize_bullet_list();

	game_state_t game_state[N_OBJECTS_TYPES];
	game_state[PLAYER].player = &player;
	game_state[BULLET].bullet_list = bullet_list;


	printf("The value of Bullet in the Object type enum is %d", BULLET);

	initialize_player_state(render, game_state);


	while (running){
		SDL_SetRenderDrawColor(render, 80, 243, 144, 255);
		SDL_RenderClear(render);

		while(SDL_PollEvent(&event) != 0){
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		actualize_player_current_state(render, game_state);
		render_game_objects(render,  game_state);
		
		SDL_Delay(TICKS_PER_FRAME);
		SDL_RenderPresent(render);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();




	return 0;

}


void render_game_objects (SDL_Renderer *render,  game_state_t* game_state){
	object_type_t different_objects[] = {PLAYER, ENEMY, BULLET};
	int each = 0;
	do{

		if (different_objects[each] == PLAYER){
			render_player_current_state(render, game_state);
		}
		else if (different_objects[each] == ENEMY){
			SDL_Log("Here we send the enemy to render\n");
		}
		else if (different_objects[each] == BULLET){
			SDL_Log("Here we send the BULLETS to render\n");
			bullet_obj_t *aux = game_state[BULLET].bullet_list->head;

			for (int i = 0; i < game_state[BULLET].bullet_list->nbullets; i++){
				SDL_Log("Rendering bullet %d out of %d\n",i+1, game_state[BULLET].bullet_list->nbullets);
				SDL_Rect crop_sprite = {0, 0, BULLET_W, BULLET_H};
				SDL_RenderCopy(render, aux->render_info.sprite, &crop_sprite, &(aux->render_info).box);
				aux = aux->prox;
			}
			
		}

		each++;
	} while (each != N_OBJECTS_TYPES);

}
