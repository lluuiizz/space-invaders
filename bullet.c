#include "include/bullet.h"
#include "include/space_invaders.h"
#include <stdlib.h>


Bullet_list *initialize_bullet_list(){
	Bullet_list *new_bullet = (Bullet_list*) malloc(sizeof(Bullet_list));

	new_bullet->head = NULL;
	new_bullet->tail = NULL;

	new_bullet->countdown = 0;
	new_bullet->nbullets  = 0;

	return new_bullet;
}

SDL_Rect get_player_rect(Object player) {
	return player.collision;
}

void set_bullet_propertys(SDL_Renderer *render, Bullet_obj *bullet, SDL_Rect player_info){
	bullet->render_info.pos_x = player_info.x + (((float)player_info.w / 2)) - ((float)BULLET_W/2);
	bullet->render_info.pos_y = player_info.y - (((float)player_info.h / 2));
	bullet->render_info.obj_type = Bullet;

	bullet->render_info.collision.w = BULLET_W;
	bullet->render_info.collision.h = BULLET_H;
	bullet->render_info.collision.x = bullet->render_info.pos_x;
	bullet->render_info.collision.y = bullet->render_info.pos_y;
	SDL_Log("Conseguimos setar a posicao e o tipo!!!\n");

	// SPRITE Creation
	SDL_Surface *bullet_surface= IMG_Load("./assets/bullet.png");
	SDL_SetSurfaceColorMod(bullet_surface, 0, 0, 0);
	bullet->render_info.sprite = SDL_CreateTextureFromSurface(render, bullet_surface);
	SDL_FreeSurface(bullet_surface);
	
}
void create_bullet(SDL_Renderer *render, Bullet_list *bullet_l, Object player){
	SDL_Log("Estamos Criando a nova bala!!\n");

	if (bullet_l == NULL)
		SDL_Log("Erro ao criar a lista de balas!\n");


	SDL_Delay(TICKS_PER_FRAME);
	printf("Player Info: %d %d %d %d\n", player.collision.w, player.collision.h, player.collision.x, player.collision.y);


	Bullet_obj *newer = (Bullet_obj*) malloc(sizeof(Bullet_obj));
	set_bullet_propertys(render, newer, player.collision);

	if (bullet_l->head == NULL)
		bullet_l->tail = newer;

	newer->prox = bullet_l->head;
	bullet_l->head = newer;

	bullet_l->nbullets++;
	bullet_l->countdown = 100;

}


