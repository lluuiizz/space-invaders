#ifndef __GAME_STATE_H
#define __GAME_STATE_H

#include "objects.h"

typedef struct game_state 
{
	player_t *player;
	enemy_grid_t *enemy_grid;

	SDL_Renderer* render;
	float delta_time;

} game_state_t;



#endif 
