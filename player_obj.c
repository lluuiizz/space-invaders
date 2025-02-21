#include "include/player_obj.h"
#include <SDL2/SDL_image.h>



void initialize_player_state(SDL_Renderer* render, Objects* player_obj) {

	SDL_Surface *player_surface = IMG_Load("./assets/player.png");
	SDL_SetSurfaceColorMod(player_surface, 0, 0, 0);
	player_obj->obj_type = Player;
	player_obj->sprite = SDL_CreateTextureFromSurface(render, player_surface);
	player_obj->pos_x = 0;
	player_obj->pos_y = 0;
	player_obj->state = -1;
	player_obj->collision.x = player_obj->pos_x; 
	player_obj->collision.y = player_obj->pos_y; 
	player_obj->collision.w = PLAYER_WIDTH; 
	player_obj->collision.h = PLAYER_HEIGHT;

}
void actualize_player_current_state(Objects* player_obj);
void render_player_current_state(SDL_Renderer* render, Objects* player_obj) {
	SDL_Rect crop_sprite = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
	SDL_RenderCopy(render, player_obj->sprite, &crop_sprite, &player_obj->collision);
}

