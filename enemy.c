#include "include/enemy.h"
#include "include/space_invaders.h"
#include <assert.h>


void initialize_enemy_list( enemy_list_t *list){

	
	list->head = NULL;
	list->nenemys = 0;

}
void create_enemy_grid(SDL_Renderer *render, game_state_t *gs)
{

	enemy_grid_t *enemy_grid = gs[ENEMY].enemy_grid;

	for (int i = 0; i < COLS_OF_ENEMYS; i++)
	{
		initialize_enemy_list(&(enemy_grid->list[i]));
		for (int j = 0; j < ROWS_OF_ENEMYS; j++)
			create_enemy(render, &(enemy_grid->list[i]), i);
		printf("\nQuantidade de inimigs na coluna %d : %d", i, enemy_grid->list[i].nenemys);
		if (enemy_grid->list[i].head == NULL)
			printf("\n\nNENHUM ELEMENTO FOI INSERIDO NA COLUNA\n\n");

	}

}
void set_enemy_pos_x(enemy_obj_t *enemy, int wich_list){
	if (wich_list == 0)
		enemy->render_info.pos_x = SPACE_BETWEEN_ENEMYS;
	else if (wich_list == COLS_OF_ENEMYS-1)
		enemy->render_info.pos_x = WIDTH- 2 *SPACE_BETWEEN_ENEMYS - ENEMY_WIDTH;
	else
		enemy->render_info.pos_x = ((wich_list+1)*SPACE_BETWEEN_ENEMYS) + wich_list * ENEMY_WIDTH; 

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
		enemy->render_info.pos_y = enemy->prox->render_info.pos_y + ENEMY_HEIGHT + SPACE_BETWEEN_ENEMYS;
	}

	enemy->render_info.box.w = ENEMY_WIDTH;
	enemy->render_info.box.h = ENEMY_HEIGHT;
	enemy->render_info.box.x = enemy->render_info.pos_x;
	enemy->render_info.box.y = enemy->render_info.pos_y;

	SDL_Surface *enemy_surface = IMG_Load("./assets/enemy.png");
	enemy->render_info.sprite = SDL_CreateTextureFromSurface(render, enemy_surface);
	SDL_FreeSurface(enemy_surface);



	
}
void create_enemy(SDL_Renderer *render, enemy_list_t *list, int wich_list)
{
	enemy_obj_t *head = list->head;
	enemy_obj_t *newer = (enemy_obj_t*) malloc(sizeof(enemy_obj_t));

	newer->prox = head;
	set_enemy_propertys(render, newer, wich_list);
	list->head = newer;

	if (list->head == NULL)
		printf("NAO FOI INSERIDO NENHUM INIMIGO!\n");

	list->nenemys++;

}

void destroy_enemy(enemy_list_t *list){
	printf("ESTAMOS DESTRUINDO O INIMIGO!!!\n");
	enemy_obj_t *to_destroy = list->head;
	if (list->head == NULL)
		return;
	if (list->head->prox != NULL){
		list->head = list->head->prox;
	}
	else {
		list->head = NULL;
	}


	free(to_destroy);
	list->nenemys--;
	printf("CONSEGUIMOS DESTRUIR O INIMIGO!!!\n");

	assert(to_destroy != NULL);
	printf("Conseguimos destruir o inimigo!\n");

}
void update_enemys(game_state_t *gs);
