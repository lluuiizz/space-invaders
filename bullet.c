#include "include/bullet.h"
#include "include/enemy.h"
#include "include/player.h"
#include "include/space_invaders.h"
#include <stdlib.h>


bullet_list_t *initialize_bullet_list()
{
	bullet_list_t *new_bullet = (bullet_list_t*) malloc(sizeof(bullet_list_t));

	new_bullet->head = NULL;
	new_bullet->tail = NULL;

	new_bullet->countdown = 0;
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


	SDL_Delay(BULLET_MOVE_SPEED/FRAMES);


	bullet_obj_t *newer = (bullet_obj_t*) malloc(sizeof(bullet_obj_t));

	set_bullet_propertys(render, newer, gs[PLAYER].player->render_info->box);

	if (bullet_list->head == NULL)
		bullet_list->tail = newer;
	else
		bullet_list->head->ant = newer;
	newer->prox = bullet_list->head;
	bullet_list->head = newer;
	bullet_list->head->ant = NULL;

	bullet_list->nbullets++;
	bullet_list->countdown = 100;

}

// Returns true if Collided with the end of the screen or an Enemy, if an enemy is hited the collumn where
// was hited is assigned to col_collided, if not then remains NULL
bool will_bullet_collide(game_state_t *gs, bullet_obj_t *bullet )
{
	if (bullet->render_info.pos_y - 1 < 0){
		return true;
	}

	
	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;

	for (int i = 0; i < COLS_OF_ENEMYS; i++){
		enemy_list_t *list = &(enemy_grid->list[i]);

		if (list->head != NULL){
			float bullet_pos_x = bullet->render_info.pos_x;
			float bullet_pos_y = bullet->render_info.pos_y;
			float enemy_pos_x  = list->head->render_info.pos_x;
			float enemy_pos_y  = list->head->render_info.pos_y;

			if ((bullet_pos_x >= enemy_pos_x) && (bullet_pos_x <= (enemy_pos_x+ENEMY_WIDTH)))
			{
				if (bullet_pos_y <= (enemy_pos_y + ENEMY_HEIGHT)){
					destroy_enemy(list);
					return true;
				}
				else 
					break;
			}
		}
		else {
			SDL_Log("\n\n\nHEAD DA COLUNA %d ESTA DESPARECIDO!!!\n\n\n", i);


		}
	}
	return false;
}

void destroy_bullet(bullet_list_t *bullet_list, bullet_obj_t *bullet)
{

	if (bullet_list->head == bullet_list->tail){
		SDL_Log("Liberando o espaço quando se há UMA BALA\n");
		bullet_list->head = NULL, bullet_list->tail = NULL;
		free(bullet);
	}
	else if (bullet->ant != NULL && bullet->prox == NULL)
	{
		SDL_Log("Liberando o espaço quando se há UMA BALA ANTERIOR\n");
		bullet_list->tail = bullet->ant;
		bullet->ant->prox = NULL;
		free(bullet);
	}
	else if (bullet->ant == NULL && bullet->prox != NULL)
	{
		SDL_Log("Liberando o espaço quando se há UMA BALA NA PROXIMA\n");
		bullet_obj_t *p_bullet = bullet;
		bullet = bullet->prox;
		bullet_list->head = bullet;
		free(p_bullet);
	}
	else if (bullet != NULL && bullet->ant != NULL && bullet->prox != NULL){	

		bullet->ant->prox = bullet->prox;
		bullet->prox->ant = bullet->ant;
		free(bullet);
	}


}

void update_bullets(game_state_t *gs)
{
	bullet_list_t *bullet_list = gs[BULLET].bullet_list;

	bullet_obj_t *aux = bullet_list->tail;


	while (aux != NULL)
	{
		if (will_bullet_collide(gs, aux) == false)
		{
			aux->render_info.pos_y -= (float)BULLET_MOVE_SPEED / FRAMES;
			aux->render_info.box.y = aux->render_info.pos_y;
			aux = aux->ant;
		}
		else 
		{
			bullet_obj_t *p_aux = aux;
			aux = aux->ant;
			destroy_bullet(bullet_list, p_aux);
			bullet_list->nbullets--;

		}
	}
}






