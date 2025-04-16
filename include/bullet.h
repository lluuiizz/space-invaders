#ifndef _BULET_H
#define _BULET_H

#include "objects.h"
#include "SDL2/SDL_image.h"


#define BULLET_MOVE_SPEED 150
#define BULLET_W 8
#define BULLET_H 8
typedef struct bullet_obj {
	Object render_info;

	struct bullet_obj *prox;

} Bullet_obj;


typedef struct {
	Bullet_obj *head;
	Bullet_obj *tail;

	int nbullets;
	int countdown;
} Bullet_list;

Bullet_list *initialize_bullet_list();
void create_bullet(SDL_Renderer *render, Bullet_list *bullet_l, Object player);
#endif 
