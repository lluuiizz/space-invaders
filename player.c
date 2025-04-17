#include "include/bullet.h"
#include "include/player.h"
#include <stdint.h>



void initialize_player_state(SDL_Renderer* render, game_state_t* gs) {

	SDL_Surface *player_surface = IMG_Load("./assets/player.png");
	SDL_SetSurfaceColorMod(player_surface, 0, 0, 0);
	gs[PLAYER].player->sprite = SDL_CreateTextureFromSurface(render, player_surface);
	SDL_FreeSurface(player_surface);
	gs[PLAYER].player->pos_x = ((float)WIDTH/2) - PLAYER_WIDTH;
	gs[PLAYER].player->pos_y = HEIGHT - PLAYER_HEIGHT;
	gs[PLAYER].player->collision.x = gs[PLAYER].player->pos_x; 
	gs[PLAYER].player->collision.y = gs[PLAYER].player->pos_y; 
	gs[PLAYER].player->collision.w = PLAYER_WIDTH; 
	gs[PLAYER].player->collision.h = PLAYER_HEIGHT;



	move_speed = 150;

}

bool will_collid_with_wall(int player_position, int movement_direction) {
	if (movement_direction == RIGHT_MOVEMENT)
		return player_position +10 > (WIDTH - PLAYER_WIDTH);
	else 
		return player_position - 10 < 0;
}

void change_player_position(game_state_t *gs, int movement_direction){
	if (movement_direction == RIGHT_MOVEMENT)
		gs[PLAYER].player->pos_x += (float )move_speed / FRAMES;
	else 
		gs[PLAYER].player->pos_x -= (float )move_speed / FRAMES;
}
void handle_keyboard_input  (SDL_Renderer *render, game_state_t *gs) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[RIGHT_MOVEMENT] && will_collid_with_wall(gs[PLAYER].player->pos_x, RIGHT_MOVEMENT) == false ) 
		change_player_position(gs, RIGHT_MOVEMENT);

	else if (keystate[LEFT_MOVEMENT] && will_collid_with_wall(gs[PLAYER].player->pos_x, LEFT_MOVEMENT) == false) 
		change_player_position(gs, LEFT_MOVEMENT);

	if (keystate[ATTACK]) 
		create_bullet(render, gs);
	else 
		printf("Fazendo nada!!!\n");
		//gs[PLAYER].player->prox->state = 0;

}
void actualize_player_current_state(SDL_Renderer* render, game_state_t* gs) {
	handle_keyboard_input(render, gs);
	gs[PLAYER].player->collision.x = gs[PLAYER].player->pos_x;
	gs[PLAYER].player->collision.y = gs[PLAYER].player->pos_y;
}
void render_player_current_state(SDL_Renderer* render, game_state_t* gs) {
	SDL_Rect crop_sprite = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
	SDL_RenderCopy(render, gs[PLAYER].player->sprite, &crop_sprite, &(gs[PLAYER].player)->collision);
}

