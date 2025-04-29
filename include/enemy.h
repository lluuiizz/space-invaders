#ifndef __ENEMY_H
#define __ENEMY_H


#include "objects.h"
#include "game_state.h"
#include <SDL2/SDL_image.h>

#define ENEMY_MOVE_SPEED 120

#define COLS_OF_ENEMYS 14
#define ROWS_OF_ENEMYS 5

#define ENEMY_WIDTH  32
#define ENEMY_HEIGHT 26
#define SPACE_BETWEEN_ENEMYS_X 12
#define SPACE_BETWEEN_ENEMYS_Y 24


typedef enum {
	MOVING,
	DYING,
	TOTAL_ENEMY_ANIMATIONS,
} enemy_animations_t;

typedef enum {
	MOVING_RIGHT,
	MOVING_LEFT,
} movement_direction_t;

typedef struct enemy_obj 
{
	object_t render_info;
	struct enemy_obj *prox;

	enemy_animations_t animation_playing;
	bool alive;

} enemy_obj_t;

struct enemy_list 
{

	enemy_obj_t *head;
	

};

struct enemy_grid 
{
	enemy_list_t list[COLS_OF_ENEMYS];
	int nenemys;
	movement_direction_t move_direction;
	unsigned int move_speed;
};


void init_enemy_list(enemy_list_t *list);
void create_enemy_grid(SDL_Renderer *render, game_state_t *gs);
void create_enemy(SDL_Renderer *render, enemy_list_t *list, int wich_col);
void update_enemys(game_state_t *gs);


#endif 
