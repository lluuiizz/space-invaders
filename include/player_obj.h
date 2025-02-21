#ifndef __PLAYER_OBJ
#define __PLAYER_OBJ

#include <SDL2/SDL_image.h>
#include "objects.h"
#include "space_invaders.h"

#define PLAYER_WIDTH  60
#define PLAYER_HEIGHT 24

#define RIGHT_MOVEMENT SDL_SCANCODE_D
#define LEFT_MOVEMENT SDL_SCANCODE_A

void initialize_player_state(SDL_Renderer* render, Objects* player_obj);
void handle_keyboard_input  (Objects* player_obj);;
void actualize_player_current_state(Objects* player_obj);
void render_player_current_state(SDL_Renderer* render, Objects* player_obj);

static int move_speed;


#endif
