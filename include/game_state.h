/**
 * @file game_state.h
 * @brief Gerenciamento do estado global do jogo.
 */

#ifndef __GAME_STATE_H
#define __GAME_STATE_H

#include "objects.h"

/**
 * @brief Estrutura que contém os componentes e variáveis de estado do jogo.
 */
typedef struct game_state
{
	player_t *player;             /**< Ponteiro para a entidade do jogador. */
	enemy_grid_t *enemy_grid;     /**< Ponteiro para a matriz de inimigos. */

	SDL_Renderer* render;         /**< Ponteiro para o renderizador do SDL2. */
	float delta_time;             /**< Tempo transcorrido entre o último quadro e o atual (em segundos). */

} game_state_t;

#endif
