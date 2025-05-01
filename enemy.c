#include "include/enemy.h"
#include "include/space_invaders.h"
#include "include/bullet.h"
#include <assert.h>


void init_enemy_list( enemy_list_t *list){
	list->head = NULL;
}

void create_enemy_grid(SDL_Renderer *render, game_state_t *gs)
{

	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;
	enemy_grid->move_direction = MOVING_RIGHT;
	enemy_grid->move_speed = 10;
	enemy_grid->nenemys = 0;

	for (int i = 0; i < COLS_OF_ENEMYS; i++)
	{
		init_enemy_list(&(enemy_grid->list[i]));
		for (int j = 0; j < ROWS_OF_ENEMYS; j++){
			create_enemy(render, &(enemy_grid->list[i]), i);
			enemy_grid->nenemys++;
		}
		assert(enemy_grid->list[i].head != NULL);

	}

}
void set_enemy_pos_x(enemy_obj_t *enemy, int wich_col){
	if (wich_col == 0)
		enemy->render_info.pos_x = SPACE_BETWEEN_ENEMYS_X;
	else if (wich_col == COLS_OF_ENEMYS-1)
		enemy->render_info.pos_x = WIDTH- 2 *SPACE_BETWEEN_ENEMYS_X - ENEMY_WIDTH;
	else
		enemy->render_info.pos_x = ((wich_col+1)*SPACE_BETWEEN_ENEMYS_X) + wich_col * ENEMY_WIDTH; 

}
void set_animation(SDL_Renderer *render, enemy_obj_t *enemy, enemy_animations_t animation_to_set ) {
	animation_t* animation = enemy->render_info.animation;
	switch (animation_to_set) {
		SDL_Surface *animation_surface;
		case MOVING:
			animation_surface = IMG_Load("./assets/enemy_moving.png");
			animation[MOVING].sprite_sheet= SDL_CreateTextureFromSurface(render, animation_surface);
			SDL_FreeSurface(animation_surface);

			animation[MOVING].frame_w = ENEMY_WIDTH;
			animation[MOVING].frame_h = ENEMY_HEIGHT;
			animation[MOVING].frame_now = -1;
			animation[MOVING].total_frames = 2; 
			animation[MOVING].time_per_frame = 1.0f;
			animation[MOVING].time_since_last = 0;
			animation[MOVING].is_looping = true;
			break;

		case DYING:
			animation_surface = IMG_Load("./assets/enemy_dying.png");
			animation[DYING].sprite_sheet= SDL_CreateTextureFromSurface(render, animation_surface);
			SDL_FreeSurface(animation_surface);
			animation[DYING].frame_w = ENEMY_WIDTH;
			animation[DYING].frame_h = ENEMY_HEIGHT;
			animation[DYING].frame_now = -1;
			animation[DYING].total_frames = 4; 
			animation[DYING].time_per_frame = 0.10f;
			animation[DYING].time_since_last = 0;
			animation[DYING].is_looping = false; 
			break;
		default:
			break;
	}
}
void set_enemy_propertys(SDL_Renderer *render, enemy_obj_t *enemy, int wich_list)
{
	printf("Criando inimigo na coluna %d\n", wich_list);

	if (enemy->prox == NULL)
	{
		set_enemy_pos_x(enemy, wich_list);
		enemy->render_info.pos_y = 0;
	}
	else
	{
		set_enemy_pos_x(enemy, wich_list);
		enemy->render_info.pos_y = enemy->prox->render_info.pos_y + ENEMY_HEIGHT + SPACE_BETWEEN_ENEMYS_Y;
	}

	enemy->render_info.box.w = ENEMY_WIDTH;
	enemy->render_info.box.h = ENEMY_HEIGHT;
	enemy->render_info.box.x = enemy->render_info.pos_x;
	enemy->render_info.box.y = enemy->render_info.pos_y;

	enemy->animation_playing = MOVING;
	enemy->alive = true;

	enemy_animations_t animation_to_set = MOVING;
	do {

		set_animation(render, enemy, animation_to_set);
		animation_to_set++;
	} while (animation_to_set != TOTAL_ENEMY_ANIMATIONS);
}
void create_enemy(SDL_Renderer *render, enemy_list_t *list, int wich_list)
{
	enemy_obj_t *head = list->head;
	enemy_obj_t *newer = (enemy_obj_t*) malloc(sizeof(enemy_obj_t));

	newer->render_info.animation = (animation_t*) malloc(sizeof(animation_t) * TOTAL_ENEMY_ANIMATIONS);

	newer->prox = head;
	set_enemy_propertys(render, newer, wich_list);
	list->head = newer;

	assert(list->head != NULL);


}

void destroy_enemy(enemy_list_t *list, enemy_obj_t *enemy){
	printf("ESTAMOS DESTRUINDO O INIMIGO!!!\n");
	enemy_obj_t *tmp = enemy;


	assert(enemy != NULL);
	assert(list->head == enemy);

	if (enemy->prox != NULL){
		enemy = enemy->prox;
	}
	else {
		enemy = NULL;
	}
	list->head = enemy;

	free(tmp->render_info.animation);
	free(tmp);
	printf("CONSEGUIMOS DESTRUIR O INIMIGO!!!\n");

	printf("Conseguimos destruir o inimigo!\n");

}
void update_animation (game_state_t *gs, enemy_obj_t *enemy) {
	enemy_animations_t animation_playing = enemy->animation_playing;
	animation_t *animation = enemy->render_info.animation;


	animation[MOVING].time_since_last += gs->delta_time;
	animation[DYING].time_since_last += gs->delta_time;
	switch (animation_playing) {
		case MOVING:
			if (animation[MOVING].frame_now == -1)// IT MEANS WHEN IS THE FIRST FRAME EVER
				animation[MOVING].frame_now++;

			else if (animation[MOVING].time_since_last >= animation[MOVING].time_per_frame) {
				animation[MOVING].frame_now++;
				animation[MOVING].frame_now %=animation[MOVING].total_frames;
				animation[MOVING].time_since_last = 0;
			}
			break;
		case DYING:
			SDL_Log("Estamos tocando a animação de morte\n");
			if (animation[DYING].frame_now == -1)
				animation[DYING].frame_now++;
			else if (animation[DYING].time_since_last >= animation[DYING].time_per_frame){
				SDL_Log("Tocando o frame %d\n", animation[DYING].frame_now);
				animation[DYING].frame_now++;
				animation[DYING].time_since_last = 0;

				if (animation[DYING].frame_now == animation[DYING].total_frames){
					enemy->alive = false;

				}
			}


			break;
		default:
			break;

	}
}

bool can_move_left(game_state_t *gs, enemy_obj_t *enemy){
	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;
	
	float tmp_pos_x = enemy->render_info.pos_x;
	tmp_pos_x -= enemy_grid->move_speed * gs->delta_time;
	
	if (tmp_pos_x > 0)
		return true;
	return false;


}
bool can_move_right(game_state_t *gs, enemy_obj_t *enemy){
	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;
	
	SDL_Log("Posicao X do inimigo: %f", enemy->render_info.pos_x);
	float tmp_pos_x = enemy->render_info.pos_x;
	tmp_pos_x += (enemy_grid->move_speed * gs->delta_time) + ENEMY_WIDTH;
	SDL_Log("TMP POS X : %f", tmp_pos_x);
	
	if (tmp_pos_x <= WIDTH)
		return true;
	return false;


}

void move_enemy(game_state_t *gs, enemy_obj_t *enemy, bool will_move_in_y){
	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;
	movement_direction_t move_direction = enemy_grid->move_direction;

	if (will_move_in_y){
		enemy->render_info.pos_y += ((float)(ENEMY_HEIGHT) / 2);
		enemy->render_info.box.y = enemy->render_info.pos_y;
	}

	switch(move_direction){
		case MOVING_RIGHT:
			enemy->render_info.pos_x += enemy_grid->move_speed * gs->delta_time;
			break;
		case MOVING_LEFT:
			enemy->render_info.pos_x -= enemy_grid->move_speed * gs->delta_time;
			break;
		default:
			break;

	}
	enemy->render_info.box.x = enemy->render_info.pos_x;
}

int farthest_column_in_direction(movement_direction_t in_move_direction, enemy_grid_t *enemy_grid){
	int indx;

	switch(in_move_direction){
		int i;
		case MOVING_RIGHT:
			for (i = COLS_OF_ENEMYS-1; i >= 0; i --)
				if (enemy_grid->list[i].head != NULL)
					break;
			indx = i;
			break;
		case MOVING_LEFT:
			for (i = 0; i < COLS_OF_ENEMYS; i++)
				if (enemy_grid->list[i].head != NULL)
					break;
			indx = i;
			break;
		default:
			break;

	}

	return indx;
}
void update_enemys(game_state_t *gs){

	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;

	if (enemy_grid->nenemys == 0)
		return;

	movement_direction_t move_direction = enemy_grid->move_direction;
	bool move_in_y_axis = false;

	int idx = farthest_column_in_direction(move_direction, enemy_grid);

	SDL_Log("O indx do mais longe eh %d\n", idx);

	create_bullet(gs->render, gs, enemy_grid->bullets);

	SDL_Log("O inimigo atirou: %d\n", enemy_grid->bullets->nbullets);



	switch (move_direction){
		case MOVING_RIGHT:
			if (!can_move_right(gs, enemy_grid->list[idx].head)){
				enemy_grid->move_direction = MOVING_LEFT;
				move_in_y_axis = true;
			}
			break;
		case MOVING_LEFT:
			if (!can_move_left(gs, enemy_grid->list[idx].head)){
				enemy_grid->move_direction = MOVING_RIGHT;
				move_in_y_axis = true;
			}
			break;
		default:
			break;
	}

	for (int i = 0; i < COLS_OF_ENEMYS; i++){
		enemy_list_t *list = &(enemy_grid->list[i]);
		enemy_obj_t *aux = list->head;

		while (aux != NULL){
			update_animation(gs, aux);
			enemy_obj_t *tmp = aux;
			aux = aux->prox;
			if (tmp->alive == false){
				SDL_Log("Aqui eu deveria chamar a função que mata o inimigo\n");
				destroy_enemy(list, tmp);
				enemy_grid->nenemys--;
			}
			else {
				move_enemy(gs, tmp, move_in_y_axis);

			}
		}
	}
}
