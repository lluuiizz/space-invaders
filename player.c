#include "include/bullet.h"
#include "include/player.h"
#include "include/space_invaders.h"
#include <stdint.h>



void initialize_player_state(SDL_Renderer* render, game_state_t* gs)
{

	gs[PLAYER].player->render_info = (object_t*) malloc(sizeof(object_t));
	SDL_Surface *player_surface = IMG_Load("./assets/player.png");
	SDL_SetSurfaceColorMod(player_surface, 0, 0, 0);
	gs[PLAYER].player->render_info->sprite = SDL_CreateTextureFromSurface(render, player_surface);
	SDL_FreeSurface(player_surface);
	gs[PLAYER].player->render_info->pos_x = ((float)WIDTH/2) - PLAYER_WIDTH;
	gs[PLAYER].player->render_info->pos_y = HEIGHT - PLAYER_HEIGHT;
	gs[PLAYER].player->render_info->box.x = gs[PLAYER].player->render_info->pos_x; 
	gs[PLAYER].player->render_info->box.y = gs[PLAYER].player->render_info->pos_y; 
	gs[PLAYER].player->render_info->box.w = PLAYER_WIDTH; 
	gs[PLAYER].player->render_info->box.h = PLAYER_HEIGHT;

	gs[PLAYER].player->move_speed = 150;


}

bool will_collid_with_wall(int player_position, int movement_direction)
{
	if (movement_direction == RIGHT_MOVEMENT)
		return player_position +10 > (WIDTH - PLAYER_WIDTH);
	else 
		return player_position - 10 < 0;
}

void change_player_position(game_state_t *gs, int movement_direction)
{
	if (movement_direction == RIGHT_MOVEMENT)
		gs[PLAYER].player->render_info->pos_x += (float )gs[PLAYER].player->move_speed / FRAMES;
	else 
		gs[PLAYER].player->render_info->pos_x -= (float )gs[PLAYER].player->move_speed / FRAMES;
}
void handle_keyboard_input  (SDL_Renderer *render, game_state_t *gs)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[RIGHT_MOVEMENT] && will_collid_with_wall(gs[PLAYER].player->render_info->pos_x, RIGHT_MOVEMENT) == false ) 
		change_player_position(gs, RIGHT_MOVEMENT);

	else if (keystate[LEFT_MOVEMENT] && will_collid_with_wall(gs[PLAYER].player->render_info->pos_x, LEFT_MOVEMENT) == false) 
		change_player_position(gs, LEFT_MOVEMENT);

	if (keystate[ATTACK]) 
		create_bullet(render, gs);
	else 
		printf("Fazendo nada!!!\n");
		//gs[PLAYER].player->prox->state = 0;

}
void actualize_player_current_state(SDL_Renderer* render, game_state_t* gs)
{
	handle_keyboard_input(render, gs);
	player_t *p_player = gs[PLAYER].player;
	p_player->render_info->box.x = p_player->render_info->pos_x;
	p_player->render_info->box.y = p_player->render_info->pos_y;
}
void render_player_current_state(SDL_Renderer* render, game_state_t* gs)
{
	SDL_Rect crop_sprite = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
	SDL_RenderCopy(render, gs[PLAYER].player->render_info->sprite, &crop_sprite, &(gs[PLAYER].player)->render_info->box);
}

