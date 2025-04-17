#ifndef __PLAYER_H
#define __PLAYER_H

#include <SDL2/SDL_image.h>
#include "objects.h"
#include "space_invaders.h"
#include "game_state.h"
#include "bullet.h"

#define PLAYER_WIDTH  60
#define PLAYER_HEIGHT 24

#define RIGHT_MOVEMENT SDL_SCANCODE_D
#define LEFT_MOVEMENT SDL_SCANCODE_A
#define ATTACK		  SDL_SCANCODE_SPACE


void initialize_player_state(SDL_Renderer* render, game_state_t *);
void handle_keyboard_input  (SDL_Renderer *render, game_state_t *);
void actualize_player_current_state(SDL_Renderer* render, game_state_t *);
void render_player_current_state(SDL_Renderer* render, game_state_t *);

static int move_speed;

#endif
