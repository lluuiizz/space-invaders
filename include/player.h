/**
 * @file player.h
 * @brief Definições da entidade do jogador.
 */

#ifndef __PLAYER_H
#define __PLAYER_H

#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "objects.h"
#include "game_state.h"

#define PLAYER_WIDTH  60  /**< Largura da nave do jogador. */
#define PLAYER_HEIGHT 24  /**< Altura da nave do jogador. */

#define RIGHT_MOVEMENT SDL_SCANCODE_D /**< Tecla para mover para a direita. */
#define LEFT_MOVEMENT SDL_SCANCODE_A  /**< Tecla para mover para a esquerda. */
#define ATTACK		  SDLK_SPACE      /**< Tecla para atirar. */

#define BULLET_PLAYER_COULDOWN 0.25   /**< Tempo de recarga entre os tiros do jogador. */
#define PLAYER_BULLET_W 6             /**< Largura do tiro do jogador. */
#define PLAYER_BULLET_H 16            /**< Altura do tiro do jogador. */

/**
 * @brief Estrutura da entidade Jogador.
 */
struct player
{
	object_t *render_info;    /**< Informações de física e renderização. */
	bool attacking;           /**< Flag indicando se o jogador deseja atirar. */
	int move_speed;           /**< Velocidade de movimento da nave. */
	bool alive;               /**< Estado vital do jogador. */
	bullet_list_t *bullets;   /**< Lista de tiros do jogador. */
};

/**
 * @brief Inicializa as variáveis e texturas do jogador.
 * @param gs Estado do jogo.
 */
void init_player_state( game_state_t *gs);

/**
 * @brief Captura a entrada do teclado para movimentar o jogador e atirar.
 * @param gs Estado do jogo.
 */
void handle_keyboard_input  ( game_state_t *gs);

/**
 * @brief Atualiza a física do jogador no quadro atual.
 * @param gs Estado do jogo.
 */
void update_player(game_state_t *gs);

/**
 * @brief Renderiza o jogador na tela.
 * @param gs Estado do jogo.
 */
void render_player_current_state(game_state_t *gs);

#endif
