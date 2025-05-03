#ifndef __PLAYER_H
#define __PLAYER_H

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "objects.h"
#include "game_state.h"

#define PLAYER_WIDTH  60
#define PLAYER_HEIGHT 24

#define RIGHT_MOVEMENT SDL_SCANCODE_D
#define LEFT_MOVEMENT SDL_SCANCODE_A
#define ATTACK		  SDLK_SPACE

#define BULLET_PLAYER_COULDOWN 0.25
#define PLAYER_BULLET_W 6
#define PLAYER_BULLET_H 16

void init_player_state( game_state_t *);
void handle_keyboard_input  ( game_state_t *);
void update_player(game_state_t *);
void render_player_current_state(game_state_t *);

struct player 
{
	object_t *render_info;
	bool attacking;
	int move_speed;

	bool alive;

	bullet_list_t *bullets;
};

#endif
