#ifndef __ENEMY_H
#define __ENEMY_H


#include "objects.h"
#include "game_state.h"
#include <SDL2/SDL_image.h>

#define ENEMY_MOVE_SPEED 120

#define COLS_OF_ENEMYS 20 
#define ROWS_OF_ENEMYS 5

#define ENEMY_WIDTH  32
#define ENEMY_HEIGHT 32
#define SPACE_BETWEEN_ENEMYS 0

typedef struct enemy_obj 
{
	object_t render_info;

	struct enemy_obj *prox;

} enemy_obj_t;

struct enemy_list 
{

	enemy_obj_t *head;

	int nenemys;
};

struct enemy_grid 
{
	enemy_list_t list[COLS_OF_ENEMYS];

};


void initialize_enemy_list(enemy_list_t *list);
void create_enemy_grid(SDL_Renderer *render, game_state_t *gs);
void create_enemy(SDL_Renderer *render, enemy_list_t *list, int wich_list);
void destroy_enemy(enemy_list_t *list);
void update_enemys(game_state_t *gs);


#endif 
