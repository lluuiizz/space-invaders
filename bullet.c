#include "include/bullet.h"
#include "include/enemy.h"
#include "include/objects.h"
#include "include/player.h"
#include "include/space_invaders.h"
#include <time.h>
#include <assert.h>
#include <stdlib.h>


bullet_list_t* init_enemy_bullet_list(){
	bullet_list_t* enemy_bullet_list = (bullet_list_t*) malloc(sizeof(bullet_list_t));

	enemy_bullet_list->couldown = 0;
	enemy_bullet_list->owner = ENEMY;
	enemy_bullet_list->head = NULL;
	enemy_bullet_list->tail = NULL;
	return enemy_bullet_list;

}
bullet_list_t* init_player_bullet_list(){
	bullet_list_t* player_bullet_list = (bullet_list_t*) malloc(sizeof(bullet_list_t));

	player_bullet_list->couldown = 0;
	player_bullet_list->owner= PLAYER;
	player_bullet_list->head = NULL;
	player_bullet_list->tail = NULL;
	return player_bullet_list;
}
bullet_list_t* initialize_bullet_list(object_type_t owner)
{
	bullet_list_t *new_bullet_list = NULL;

	switch(owner){
		case PLAYER:
			new_bullet_list = init_player_bullet_list();
			break;
		case ENEMY:
			new_bullet_list = init_enemy_bullet_list();
			SDL_Log("Owner of the bullet List: Enemy\n");
			break;
		default:
				break;
	}
	assert(new_bullet_list != NULL);
	assert(new_bullet_list->head == NULL);
	assert(new_bullet_list->tail == NULL);
	new_bullet_list->nbullets = 0;


	return new_bullet_list;
}


void set_enemy_bullet_propertys(SDL_Renderer *render, game_state_t *gs, bullet_obj_t* bullet){
	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;

	unsigned int random_col;
	srand(time(NULL));
	do{
		random_col = rand() % COLS_OF_ENEMYS;
	}while (enemy_grid->list[random_col].head == NULL);

	SDL_Rect enemy_box = enemy_grid->list[random_col].head->render_info.box;
	bullet->render_info.pos_x = enemy_box.x + (((float)enemy_box.w / 2)) - ((float)BULLET_W/2);
	bullet->render_info.pos_y = enemy_box.y + (((float)enemy_box.h / 2)) + ((float)BULLET_H/2);
	bullet->render_info.box.x = bullet->render_info.pos_x;
	bullet->render_info.box.y = bullet->render_info.pos_y;

	bullet->render_info.box.w = BULLET_W;
	bullet->render_info.box.h = BULLET_H;

	SDL_Surface *bullet_surface= IMG_Load("./assets/enemy_bullet.png"); assert(bullet_surface != NULL);
	bullet->render_info.sprite = SDL_CreateTextureFromSurface(render, bullet_surface);
	SDL_FreeSurface(bullet_surface);
}

void set_player_bullet_propertys(SDL_Renderer *render, game_state_t *gs, bullet_obj_t *bullet){
	SDL_Rect player_box = gs[PLAYER].player->render_info->box;
	bullet->render_info.pos_x = player_box.x + (((float)player_box.w / 2)) - ((float)BULLET_W/2);
	bullet->render_info.pos_y = player_box.y - (((float)player_box.h / 2)) - ((float)BULLET_H/2);

	bullet->render_info.box.w = BULLET_W;
	bullet->render_info.box.h = BULLET_H;
	bullet->render_info.box.x = bullet->render_info.pos_x;
	bullet->render_info.box.y = bullet->render_info.pos_y;
	SDL_Log("Conseguimos setar a posicao e o tipo!!!\n");

	// SPRITE Creation
	SDL_Surface *bullet_surface= IMG_Load("./assets/bullet.png"); assert(bullet_surface != NULL);

	bullet->render_info.sprite = SDL_CreateTextureFromSurface(render, bullet_surface);
	SDL_FreeSurface(bullet_surface);
}
void create_bullet(SDL_Renderer *render, game_state_t *gs, bullet_list_t* bullet_list)
{
	SDL_Log("Estamos Criando a nova bala!!\n");


	assert(bullet_list != NULL);

	if (bullet_list->couldown > 0)
		return;

	bullet_obj_t *newer = (bullet_obj_t*) malloc(sizeof(bullet_obj_t));

	switch (bullet_list->owner){
		case PLAYER:
			set_player_bullet_propertys(render, gs, newer);
			break;
		case ENEMY:
			SDL_Log("Tentando criar BALA para ENEMY\n");
			set_enemy_bullet_propertys(render, gs, newer);
			break;
		default:
			break;
	}
	if (bullet_list->head == NULL) {
		bullet_list->tail = newer;
		bullet_list->tail->prox = NULL;
	}
	else
		bullet_list->head->ant = newer;

	newer->prox = bullet_list->head;
	bullet_list->head = newer;
	bullet_list->head->ant = NULL;

	bullet_list->nbullets++;
	bullet_list->couldown = (bullet_list->owner == PLAYER) ? BULLET_PLAYER_COULDOWN : BULLET_ENEMY_COULDOWN;

}




bool check_collision_with_player(game_state_t *gs, bullet_obj_t *bullet){
	player_t *player = gs[PLAYER].player;
	SDL_Rect player_box = player->render_info->box;

	bool collided = false;


	if ((bullet->render_info.pos_x + BULLET_W) > player_box.x && bullet->render_info.pos_x < (player_box.x+player_box.w)){
		SDL_Log("Colidiu no eixo X");
		if((bullet->render_info.pos_y+BULLET_H) > player_box.y && (bullet->render_info.pos_y < player_box.y + player_box.h))
			collided = true;
	}
	return collided;
}
bool check_collision_with_enemy(game_state_t *gs, bullet_obj_t *bullet){
	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;
	bool collided = false;

	for (int i = 0; i < COLS_OF_ENEMYS; i++){
		enemy_list_t *list = &(enemy_grid->list[i]);

		if (list->head != NULL && list->head->animation_playing != DYING){
			float bullet_pos_x = bullet->render_info.pos_x;
			float bullet_pos_y = bullet->render_info.pos_y;
			float enemy_pos_x  = list->head->render_info.pos_x;
			float enemy_pos_y  = list->head->render_info.pos_y;

			bool x_collision = (bullet_pos_x + BULLET_W > enemy_pos_x) && (bullet_pos_x < enemy_pos_x + ENEMY_WIDTH);
			bool y_collision = (bullet_pos_y + BULLET_H > enemy_pos_y) &&
                               (bullet_pos_y < enemy_pos_y + ENEMY_HEIGHT);

			if (x_collision && y_collision){
				SDL_Log("Matamos um inimigo!\n");
				list->head->animation_playing = DYING;
				assert(list->head->animation_playing == DYING);
				collided = true;
				break;
			}
		}
	}
	return collided;
}
bool will_bullet_collide(game_state_t *gs, bullet_obj_t *bullet, object_type_t owner )
{
	if (owner == PLAYER && bullet->render_info.pos_y - 1 < 0)
		return true;

	if (owner == ENEMY && bullet->render_info.pos_y+1 > HEIGHT)
		return true;

	bool result;
	if (owner == PLAYER)
		result = check_collision_with_enemy(gs, bullet);
	else if (owner == ENEMY)
		result = check_collision_with_player(gs, bullet);

	
	return result;
}

void destroy_bullet(bullet_list_t *bullet_list, bullet_obj_t *bullet)
{

	if (bullet_list->head == bullet_list->tail){
		SDL_Log("DESTRUINDO a BALA quando se há APENAS UMA \n");
		bullet_list->head = NULL, bullet_list->tail = NULL;
		free(bullet);
	}
	else if (bullet->ant != NULL && bullet->prox == NULL)
	{
		SDL_Log("DESTRUINDO a BALA quando se há UMA NA ANTERIO\n");
		bullet_list->tail = bullet->ant;
		bullet->ant->prox = NULL;
		free(bullet);
	}
	else if (bullet->ant == NULL && bullet->prox != NULL)
	{
		SDL_Log("DESTRUINDO a BALA quando se há UMA NA PROXIMA\n");
		bullet_list->head = bullet->prox;
		free(bullet);
	}
	else if (bullet != NULL && bullet->ant != NULL && bullet->prox != NULL){	
		SDL_Log("DESTRUINDO a BALA quando se há uma NA ANTERIOR E PROXIMA\n");
		bullet->ant->prox = bullet->prox;
		bullet->prox->ant = bullet->ant;
		bullet->prox = NULL;
		bullet->ant  = NULL;
		free(bullet);
	}

	bullet_list->nbullets--;

}

void update_bullets(game_state_t *gs)
{
	bullet_list_t *player_bullets = gs[PLAYER].player->bullets;
	bullet_list_t *enemy_bullets = gs[ENEMY].enemy_grid->bullets;

	player_bullets->couldown -= gs->delta_time;
	enemy_bullets->couldown -= gs->delta_time;


	bullet_obj_t *player_aux = player_bullets->head;
	bullet_obj_t *enemy_aux = enemy_bullets->head;



	while (player_aux != NULL)
	{
		if (will_bullet_collide(gs, player_aux, PLAYER) == false)
		{
			player_aux->render_info.pos_y -= (float)BULLET_MOVE_SPEED * gs->delta_time;
			player_aux->render_info.box.y = player_aux->render_info.pos_y;
			player_aux = player_aux->prox;
		}
		else 
		{
			bullet_obj_t *p_player_aux = player_aux;
			player_aux = player_aux->prox;
			destroy_bullet(player_bullets, p_player_aux);

		}
	}
	while (enemy_aux != NULL)
	{
		if (will_bullet_collide(gs, enemy_aux, ENEMY) == false)
		{
			enemy_aux->render_info.pos_y += (float)(BULLET_MOVE_SPEED/2) * gs->delta_time;
			enemy_aux->render_info.box.y = enemy_aux->render_info.pos_y;
			enemy_aux = enemy_aux->prox;
		}
		else
		{
			bullet_obj_t *p_enemy_aux = enemy_aux;
			enemy_aux = enemy_aux->prox;
			destroy_bullet(enemy_bullets, p_enemy_aux);
		}
	}
}






