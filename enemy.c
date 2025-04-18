#include "include/enemy.h"


enemy_list_t *initialize_enemy_list();
void create_enemy(SDL_Renderer *render, game_state_t *gs);
void update_enemys(game_state_t *gs);
