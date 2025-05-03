#include "include/space_invaders.h"
#include "include/bullet.h"

#include <assert.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Erro ao inicializar o SDL2: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	assert(window != NULL);
	SDL_Log("Janela criada com sucesso!\n");

	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	assert(render != NULL);
	SDL_Log("Render criado com sucesso!\n");

	bool running = true;
	SDL_Event event;

	player_t player;
	enemy_grid_t enemy_grid;

	game_state_t* gs = (game_state_t*) malloc(sizeof(game_state_t));
	gs->player = &player;
	gs->enemy_grid = &enemy_grid;
	gs->render = render;

	assert(gs != NULL);

	init_player_state(gs);

	SDL_Log("Inicializamos o Player\n");
	player.bullets = initialize_bullet_list(PLAYER);
	SDL_Log("Inicializamos As Balas do Player\n");
	assert(player.bullets != NULL);
	assert(player.bullets->head == NULL);

	create_enemy_grid(gs);
	SDL_Log("Inicializamos a matriz de Inimigos\n");
	enemy_grid.bullets = initialize_bullet_list(ENEMY);

	assert(enemy_grid.bullets != NULL);
	assert(enemy_grid.bullets->head == NULL);

	SDL_Log("Conseguimos passar por toda a inicialização!\n");
	Uint32 last_time = SDL_GetTicks();

	while (running)
	{
		// Actualize delta time
		Uint32 now = SDL_GetTicks();
		gs->delta_time = (now - last_time) / 1000.0f;
		last_time = now;

		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);

		while(SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				running = false;
			// Check if the Space button was released and then set flag attack to true
			else if (event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == ATTACK){
					gs->player->attacking = true;
				}
			}
		}
		SDL_Log("Vamos começar a atualizar os dados\n");
		update_player(gs);
		update_bullets(gs);
		update_enemys (gs);
		render_game_objects(render,  gs);

		SDL_Delay(TICKS_PER_FRAME);
		SDL_RenderPresent(render);
	}


	assert(player.bullets->head == NULL && player.bullets->tail == NULL);
	assert(enemy_grid.bullets->head == NULL && enemy_grid.bullets->tail == NULL);

	free(player.bullets);
	free(player.render_info);
	free(enemy_grid.bullets);

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
			render_player_current_state (gs);
		}

		else if (different_objects[each] == ENEMY){
			enemy_grid_t *enemy_grid = gs->enemy_grid;
			for (int i = 0; i < COLS_OF_ENEMYS; i++){
				enemy_list_t *list = &(enemy_grid->list[i]);
				enemy_obj_t *aux = list->head;
				while (aux != NULL){
					animation_t *animation = aux->render_info.animation;
					animation_t animation_now = animation[aux->animation_playing];
					SDL_Rect crop_sprite = {.x = animation_now.frame_w * animation_now.frame_now,
											.y = 0,
											.w = ENEMY_WIDTH,
											.h =  ENEMY_HEIGHT};

					SDL_RenderCopy(render, animation_now.sprite_sheet, &crop_sprite, &(aux->render_info).box);
					aux = aux->prox;
				}
			}
		}

		else if (different_objects[each] == BULLET)
		{
			SDL_Log("Here we send the BULLETS to render\n");
			bullet_obj_t *player_aux = gs->player->bullets->head;
			bullet_obj_t *enemy_aux = gs->enemy_grid->bullets->head;

			while (player_aux != NULL){
				SDL_Log("Estamos tentando renderizar uma bala\n");
				SDL_Rect sprite_rect = {.x = 0, .y = 0, .w = 8, .h = 16};
				SDL_RenderCopy(render, player_aux->render_info.sprite, &sprite_rect, &(player_aux->render_info).box);
				player_aux = player_aux->prox;
			}
			while (enemy_aux != NULL){
				SDL_Log("Estamos tentando renderizar uma bala\n");
				SDL_Rect sprite_rect = {.x = 0, .y = 0, .w = 8, .h = 16};
				SDL_RenderCopy(render, enemy_aux->render_info.sprite, &sprite_rect, &(enemy_aux->render_info).box);
				enemy_aux = enemy_aux->prox;
			}
		}

		each++;
	} while (each != N_OBJECTS_TYPES);

}
