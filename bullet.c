#include "include/bullet.h"
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


	SDL_Delay(TICKS_PER_FRAME);


	bullet_obj_t *newer = (bullet_obj_t*) malloc(sizeof(bullet_obj_t));

	set_bullet_propertys(render, newer, gs[PLAYER].player->render_info->box);

	if (bullet_list->head == NULL)
		bullet_list->tail = newer;

	newer->prox = gs[BULLET].bullet_list->head;
	bullet_list->head = newer;

	bullet_list->nbullets++;
	bullet_list->countdown = 100;

}

bool will_bullet_collide(bullet_obj_t *bullet)
{
	if (bullet->render_info.pos_y - 1 < 0)
		return true;

	return false;
}

void update_bullets(game_state_t *gs)
{
	bullet_list_t *bullet_list = gs[BULLET].bullet_list;

	bullet_obj_t *aux = bullet_list->head;


	while (aux != NULL)
	{
		if (will_bullet_collide(aux) == false)
		{
			aux->render_info.pos_y -= (float)BULLET_MOVE_SPEED / FRAMES;
			aux->render_info.box.y = aux->render_info.pos_y;
		}

		aux = aux->prox;
	}

}






