#ifndef _BULET_H
#define _BULET_H

#include "objects.h"
#include "game_state.h"
#include "SDL2/SDL_image.h"


#define BULLET_MOVE_SPEED 150
#define BULLET_W 32
#define BULLET_H 32

typedef struct bullet_obj
{
	object_t render_info;

	struct bullet_obj *prox;

} bullet_obj_t;

struct bullet_list
{
	bullet_obj_t *head;
	bullet_obj_t *tail;

	int nbullets;
	int countdown;
};


bullet_list_t *initialize_bullet_list();
void create_bullet(SDL_Renderer *render, game_state_t *);
void update_bullets(game_state_t *gs);
#endif 
