#ifndef _BULET_H
#define _BULET_H

#include "objects.h"
#include "game_state.h"
#include "SDL2/SDL_image.h"


typedef struct bullet_obj
{
	object_t render_info;

	struct bullet_obj *prox;
	struct bullet_obj *ant;

} bullet_obj_t;

struct bullet_list
{
	bullet_obj_t *head;
	bullet_obj_t *tail;

	int nbullets;
	float couldown;
	int move_speed;

	object_type_t owner;
};


bullet_list_t *initialize_bullet_list(object_type_t owner);
void create_bullet(SDL_Renderer *render, game_state_t* gs, bullet_list_t* bullet_list);
void update_bullets(game_state_t *gs);
#endif 
