#ifndef __PLAYER_H
#define __PLAYER_H

#include <SDL2/SDL_image.h>
#include "objects.h"
#include "space_invaders.h"
#include "bullet.h"

#define PLAYER_WIDTH  60
#define PLAYER_HEIGHT 24

#define RIGHT_MOVEMENT SDL_SCANCODE_D
#define LEFT_MOVEMENT SDL_SCANCODE_A
#define ATTACK		  SDL_SCANCODE_SPACE


void initialize_player_state(SDL_Renderer* render, Object* player_obj);
void handle_keyboard_input  (SDL_Renderer *render, Bullet_list *bullet_list, Object* player_obj);
void actualize_player_current_state(SDL_Renderer* render, Bullet_list *bullet_list, Object* player_obj);
void render_player_current_state(SDL_Renderer* render, Object* player_obj);

static int move_speed;

#endif
