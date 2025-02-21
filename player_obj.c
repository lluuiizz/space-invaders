#include "include/player_obj.h"
#include <stdint.h>



void initialize_player_state(SDL_Renderer* render, Objects* player_obj) {

	SDL_Surface *player_surface = IMG_Load("./assets/player.png");
	SDL_SetSurfaceColorMod(player_surface, 0, 0, 0);
	player_obj->obj_type = Player;
	player_obj->sprite = SDL_CreateTextureFromSurface(render, player_surface);
	SDL_FreeSurface(player_surface);
	player_obj->pos_x = ((float)WIDTH/2) - PLAYER_WIDTH;
	player_obj->pos_y = HEIGHT - PLAYER_HEIGHT;
	player_obj->state = -1;
	player_obj->collision.x = player_obj->pos_x; 
	player_obj->collision.y = player_obj->pos_y; 
	player_obj->collision.w = PLAYER_WIDTH; 
	player_obj->collision.h = PLAYER_HEIGHT;

	move_speed = 150;

}

void handle_keyboard_input  (Objects* player_obj) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[RIGHT_MOVEMENT] ) {
		if (player_obj->pos_x + 10 < (WIDTH - PLAYER_WIDTH)) 
			player_obj->pos_x += (float )move_speed / FRAMES;

		actualize_player_current_state(player_obj);
	}
	else if (keystate[LEFT_MOVEMENT]) {
		if (player_obj->pos_x - 10 > 0) 
			player_obj->pos_x -= (float )move_speed / FRAMES;
		actualize_player_current_state(player_obj);
	}

}
void actualize_player_current_state(Objects* player_obj) {
	player_obj->collision.x = player_obj->pos_x;
	player_obj->collision.y = player_obj->pos_y;
}
void render_player_current_state(SDL_Renderer* render, Objects* player_obj) {
	SDL_Rect crop_sprite = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
	SDL_RenderCopy(render, player_obj->sprite, &crop_sprite, &player_obj->collision);
}

