#ifndef __GAME_STATE_H
#define __GAME_STATE_H

#include "objects.h"


#define N_GAME_ENTITYS 3

typedef struct game_state 
{
	union 
	{
		bullet_list_t *bullet_list;
		player_t *player;
	};

} game_state_t;



#endif 
