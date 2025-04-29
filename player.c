#include "include/bullet.h"
#include "include/player.h"
#include "include/space_invaders.h"
#include <stdint.h>



void init_player_state(SDL_Renderer* render, game_state_t* gs)
{
	player_t *player = gs[PLAYER].player;

	player->render_info = (object_t*) malloc(sizeof(object_t));
	SDL_Surface *player_surface = IMG_Load("./assets/player.png");
	player->render_info->sprite = SDL_CreateTextureFromSurface(render, player_surface);
	SDL_FreeSurface(player_surface);
	player->render_info->pos_x = ((float)WIDTH/2) - PLAYER_WIDTH;
	player->render_info->pos_y = HEIGHT - PLAYER_HEIGHT;
	player->render_info->box.x = player->render_info->pos_x; 
	player->render_info->box.y = player->render_info->pos_y; 
	player->render_info->box.w = PLAYER_WIDTH; 
	player->render_info->box.h = PLAYER_HEIGHT;

	player->move_speed = 150;
	player->attacking = false;


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
		gs[PLAYER].player->render_info->pos_x += (gs[PLAYER].player->move_speed * gs->delta_time);
	else 
		gs[PLAYER].player->render_info->pos_x -= (gs[PLAYER].player->move_speed * gs->delta_time);
}
void handle_keyboard_input  (SDL_Renderer *render, game_state_t *gs)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[RIGHT_MOVEMENT] && will_collid_with_wall(gs[PLAYER].player->render_info->pos_x, RIGHT_MOVEMENT) == false ) 
		change_player_position(gs, RIGHT_MOVEMENT);

	else if (keystate[LEFT_MOVEMENT] && will_collid_with_wall(gs[PLAYER].player->render_info->pos_x, LEFT_MOVEMENT) == false) 
		change_player_position(gs, LEFT_MOVEMENT);

	if (gs[PLAYER].player->attacking) {
		create_bullet(render, gs);
		gs[PLAYER].player->attacking = false;
	}
	else 
		printf("Fazendo nada!!!\n");
		//gs[PLAYER].player->prox->state = 0;

}
void update_player(SDL_Renderer* render, game_state_t* gs)
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

