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

	// Inicializa a bala!!!
	/*
	Objects *create_bullet = (Objects*) malloc(sizeof(Objects));
	SDL_Surface *player_bullet = IMG_Load("./assets/bullet.png");
	create_bullet->sprite = SDL_CreateTextureFromSurface(render, player_bullet);
	create_bullet->pos_x = player_obj->pos_x + (float)PLAYER_WIDTH/2;
	create_bullet->pos_y = player_obj->pos_y - 2*PLAYER_HEIGHT;
	create_bullet->collision.x = create_bullet->prox->pos_x; 
	create_bullet->collision.y = create_bullet->pos_y; 
	create_bullet->collision.w = 2;
	create_bullet->collision.h = 8;

	player_obj->prox = create_bullet;
	*/


	move_speed = 150;

}

bool will_collid_with_wall(int player_position, int movement_direction) {
	if (movement_direction == RIGHT_MOVEMENT)
		return player_position +10 > (WIDTH - PLAYER_WIDTH);
	else 
		return player_position - 10 < 0;
}

void change_player_position(Objects *player_obj, int movement_direction){
	if (movement_direction == RIGHT_MOVEMENT)
		player_obj->pos_x += (float )move_speed / FRAMES;
	else 
		player_obj->pos_x -= (float )move_speed / FRAMES;
}
void handle_keyboard_input  (Objects* player_obj) {
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[RIGHT_MOVEMENT] && will_collid_with_wall(player_obj->pos_x, RIGHT_MOVEMENT) == false ) 
		change_player_position(player_obj, RIGHT_MOVEMENT);

	else if (keystate[LEFT_MOVEMENT] && will_collid_with_wall(player_obj->pos_x, LEFT_MOVEMENT) == false) 
		change_player_position(player_obj, LEFT_MOVEMENT);
	else if (keystate[ATTACK]) 
		printf("Vai atirar!!!\n");
		//player_obj->prox->state = 1;
	else 
		printf("Fazendo nada!!!\n");
		//player_obj->prox->state = 0;

}
void actualize_player_current_state(Objects* player_obj) {
	player_obj->collision.x = player_obj->pos_x;
	player_obj->collision.y = player_obj->pos_y;

	/*
	// Atualiza a posição de onde sairia a bala
	player_obj->prox->pos_x = player_obj->pos_x + (float)PLAYER_WIDTH/2;
	player_obj->prox->pos_y = player_obj->pos_y - 2*PLAYER_HEIGHT;
	player_obj->prox->collision.x = player_obj->prox->pos_x; 
	player_obj->prox->collision.y = player_obj->prox->pos_y; 
	*/
}
void render_player_current_state(SDL_Renderer* render, Objects* player_obj) {
	handle_keyboard_input(player_obj);
	actualize_player_current_state(player_obj);
	SDL_Rect crop_sprite = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
	SDL_RenderCopy(render, player_obj->sprite, &crop_sprite, &player_obj->collision);
}

