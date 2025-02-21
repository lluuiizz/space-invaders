#ifndef __PLAYER_OBJ
#define __PLAYER_OBJ

#include "objects.h"

#define PLAYER_WIDTH  60
#define PLAYER_HEIGHT 24

void initialize_player_state(SDL_Renderer* render, Objects* player_obj);
void actualize_player_current_state(Objects* player_obj);
void render_player_current_state(SDL_Renderer* render, Objects* player_obj);


#endif
