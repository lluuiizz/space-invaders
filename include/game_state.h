#ifndef __GAME_STATE_H
#define __GAME_STATE_H

#include "objects.h"

typedef struct game_state 
{
	union 
	{
		player_t *player;
		enemy_grid_t *enemy_grid;
		bullet_list_t *bullet_list;
	};

} game_state_t;



#endif 
