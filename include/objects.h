#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <SDL2/SDL.h>

typedef enum {
	Player,
	Enemy,

} Object_type;

typedef struct object {
	Object_type  obj_type;
	SDL_Texture* sprite;
	int          state;
	int		     pos_x, pos_y;
	SDL_Rect	 collision;	//dst_rect:  pos_x pos_y, width_height
	
	struct object* prox;
	

} Objects;




#endif
