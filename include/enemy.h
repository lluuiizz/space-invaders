#ifndef __ENEMY_H
#define __ENEMY_H


#include "objects.h"
#include "game_state.h"
#include <SDL2/SDL_image.h>

#define ENEMY_MOVE_SPEED 120

typedef struct enemy_obj 
{
	object_t render_info;

	struct enemy_obj *prox;
	struct enemy_obj *ant ;

} enemy_obj_t;

struct enemy_list 
{

	enemy_obj_t *head;
	enemy_obj_t *tail;

	int nenemys;
};

enemy_list_t *initialize_enemy_list();
void create_enemy(SDL_Renderer *render, game_state_t *gs);
void update_enemys(game_state_t *gs);


#endif 
