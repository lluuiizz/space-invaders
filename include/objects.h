#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <SDL2/SDL.h>

typedef enum {
	Player,
	Enemy,
	Bullet,

} Object_type;
#define NUM_OF_DIFFERENT_OBJECTS 3

typedef struct {
	Object_type  obj_type;
	SDL_Texture* sprite;
	float		 pos_x, pos_y;
	SDL_Rect	 collision;	//dst_rect:  pos_x pos_y, width_height
	
} Object;

typedef Object* Objects;




#endif
