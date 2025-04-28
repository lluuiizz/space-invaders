#include "include/bullet.h"
#include "include/enemy.h"
#include "include/player.h"
#include "include/space_invaders.h"
#include <assert.h>
#include <stdlib.h>


bullet_list_t *initialize_bullet_list()
{
	bullet_list_t *new_bullet = (bullet_list_t*) malloc(sizeof(bullet_list_t));

	new_bullet->head = NULL;
	new_bullet->tail = NULL;

	new_bullet->couldown = 0.0f;
	new_bullet->nbullets  = 0;

	return new_bullet;
}


void set_bullet_propertys(SDL_Renderer *render, bullet_obj_t *bullet, SDL_Rect player_info)
{
	bullet->render_info.pos_x = player_info.x + (((float)player_info.w / 2)) - ((float)BULLET_W/2);
	bullet->render_info.pos_y = player_info.y - (((float)player_info.h / 2)) - ((float)BULLET_H/2);

	bullet->render_info.box.w = BULLET_W;
	bullet->render_info.box.h = BULLET_H;
	bullet->render_info.box.x = bullet->render_info.pos_x;
	bullet->render_info.box.y = bullet->render_info.pos_y;
	SDL_Log("Conseguimos setar a posicao e o tipo!!!\n");

	// SPRITE Creation
	SDL_Surface *bullet_surface= IMG_Load("./assets/bullet.png");
	bullet->render_info.sprite = SDL_CreateTextureFromSurface(render, bullet_surface);
	SDL_FreeSurface(bullet_surface);
	
}
void create_bullet(SDL_Renderer *render, game_state_t *gs)
{
	SDL_Log("Estamos Criando a nova bala!!\n");

	bullet_list_t *bullet_list = gs[BULLET].bullet_list;
	if (bullet_list == NULL)
		SDL_Log("Erro ao criar a lista de balas!\n");

	if (bullet_list->couldown > 0)
		return;

	bullet_obj_t *newer = (bullet_obj_t*) malloc(sizeof(bullet_obj_t));

	set_bullet_propertys(render, newer, gs[PLAYER].player->render_info->box);

	if (bullet_list->head == NULL){
		bullet_list->tail = newer;
		bullet_list->tail->prox = NULL;
	}
	else
		bullet_list->head->ant = newer;
	newer->prox = bullet_list->head;
	bullet_list->head = newer;
	bullet_list->head->ant = NULL;

	bullet_list->nbullets++;
	bullet_list->couldown = BULLET_PLAYER_COULDOWN;

}

// Returns true if Collided with the end of the screen or an Enemy, if an enemy is hited the collumn where
// was hited is assigned to col_collided, if not then remains NULL
bool will_bullet_collide(game_state_t *gs, bullet_obj_t *bullet )
{
	if (bullet->render_info.pos_y - 1 < 0){
		return true;
	}

	
	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;
	bool collided = false;

	for (int i = 0; i < COLS_OF_ENEMYS; i++){
		enemy_list_t *list = &(enemy_grid->list[i]);

		if (list->head != NULL){
			float bullet_pos_x = bullet->render_info.pos_x;
			float bullet_pos_y = bullet->render_info.pos_y;
			float enemy_pos_x  = list->head->render_info.pos_x;
			float enemy_pos_y  = list->head->render_info.pos_y;

			bool x_collision = (bullet_pos_x + BULLET_W > enemy_pos_x) && (bullet_pos_x < enemy_pos_x + ENEMY_WIDTH);
			bool y_collision = (bullet_pos_y + BULLET_H > enemy_pos_y) && 
                               (bullet_pos_y < enemy_pos_y + ENEMY_HEIGHT);

			if (x_collision && y_collision){
				destroy_enemy(list);
				collided = true;
				break;
			}
		}
	}
	return collided;
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
	bullet_list_t *bullet_list = gs[BULLET].bullet_list;

	bullet_list->couldown -= gs->delta_time;

	bullet_obj_t *aux = bullet_list->head;


	while (aux != NULL)
	{
		if (will_bullet_collide(gs, aux) == false)
		{
			aux->render_info.pos_y -= (float)BULLET_MOVE_SPEED / FRAMES;
			aux->render_info.box.y = aux->render_info.pos_y;
			aux = aux->prox;
		}
		else 
		{
			bullet_obj_t *p_aux = aux;
			aux = aux->prox;
			destroy_bullet(bullet_list, p_aux);

		}
	}
}






