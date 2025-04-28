#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <SDL2/SDL.h>
#include "animation.h"

typedef enum 
{
	PLAYER,
	ENEMY,
	BULLET,
	N_OBJECTS_TYPES,
} object_type_t;

typedef struct 
{
	union {
		SDL_Texture* sprite;
		animation_t* animation;
	};

	float		 pos_x, pos_y;
	SDL_Rect	 box;	
	
} object_t;



typedef struct player player_t;
typedef struct enemy_list enemy_list_t;
typedef struct enemy_grid enemy_grid_t;
typedef struct bullet_list bullet_list_t;


#endif
