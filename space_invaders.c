#include "include/space_invaders.h"
#include "include/game_state.h"
#include "include/objects.h"
#include "include/player.h"
#include "include/enemy.h"
#include "include/bullet.h"
#include <stdlib.h>

int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erro ao inicializar o SDL2: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Erro ao criar janela: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (render == NULL)
	{
		printf("Erro ao criar render: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	bool running = true;
	SDL_Event event;

	player_t player;
	enemy_grid_t enemy_grid; 
	bullet_list_t *bullet_list = initialize_bullet_list();

	game_state_t gs[N_OBJECTS_TYPES];
	gs[PLAYER].player = &player;
	gs[ENEMY].enemy_grid = &enemy_grid;
	gs[BULLET].bullet_list = bullet_list;


	printf("The value of Bullet in the Object type enum is %d", BULLET);

	initialize_player_state(render, gs);
	create_enemy_grid(render, gs);


	while (running)
	{
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);

		while(SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				running = false;
		}

		actualize_player_current_state(render, gs);
		update_bullets(gs);
		render_game_objects(render,  gs);
		
		SDL_Delay(TICKS_PER_FRAME);
		SDL_RenderPresent(render);
	}

	if (bullet_list->head == NULL && bullet_list->tail == NULL)
		printf("Finalizamos com HEAD E TAIL - NULL\n");
	free(bullet_list);
	free(player.render_info);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_Quit();




	return 0;

}


void collision_debug_rect(SDL_Renderer *render, object_t *object){

	SDL_Rect debug_rect  = {.x = object->pos_x, .y = object->pos_y, .w= object->box.w, .h = object->box.h};
	SDL_SetRenderDrawColor(render, 255, 0, 0, 100);
	SDL_RenderFillRect(render, &debug_rect);
}
void render_game_objects (SDL_Renderer *render,  game_state_t* gs)
{
	object_type_t different_objects[] = {PLAYER, ENEMY, BULLET};
	int each = 0;
	do
	{

		if (different_objects[each] == PLAYER){
			collision_debug_rect(render, gs[PLAYER].player->render_info);
			render_player_current_state(render, gs);
		}

		else if (different_objects[each] == ENEMY){
			enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;
			for (int i = 0; i < COLS_OF_ENEMYS; i++){
				enemy_list_t *list = &(enemy_grid->list[i]);
				enemy_obj_t *aux = list->head;
				while (aux != NULL){
					aux->which_sprite = (aux->which_sprite == 0) ? 1 : 0;
					SDL_Rect crop_sprite = {.x = (aux->which_sprite * ENEMY_WIDTH),.y = 0,.w = ENEMY_WIDTH,.h =  ENEMY_HEIGHT};
					collision_debug_rect(render, &(aux->render_info));
					SDL_RenderCopy(render, aux->render_info.sprite, &crop_sprite, &(aux->render_info).box);
					aux = aux->prox;
				}
			}
		}

		else if (different_objects[each] == BULLET)
		{
			SDL_Log("Here we send the BULLETS to render\n");
			bullet_obj_t *aux = gs[BULLET].bullet_list->head;

			while (aux != NULL){
				SDL_Rect crop_sprite = {.x = 0,.y = 0,.w = BULLET_W,.h =  BULLET_H};
				collision_debug_rect(render, &(aux->render_info));
				SDL_RenderCopy(render, aux->render_info.sprite, &crop_sprite, &(aux->render_info).box);
				aux = aux->prox;
			}
		}

		each++;
	} while (each != N_OBJECTS_TYPES);

}
