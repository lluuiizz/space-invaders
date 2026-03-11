/**
 * @file enemy.h
 * @brief Definições da horda de inimigos.
 */

#ifndef __ENEMY_H
#define __ENEMY_H

#include "objects.h"
#include "game_state.h"
#include <SDL2/SDL_image.h>

#define ENEMY_MOVE_SPEED 120
#define BULLET_ENEMY_COULDOWN 1

#define COLS_OF_ENEMYS 14
#define ROWS_OF_ENEMYS 5

#define ENEMY_WIDTH  32
#define ENEMY_HEIGHT 26
#define ENEMY_BULLET_W 7
#define ENEMY_BULLET_H 16
#define SPACE_BETWEEN_ENEMYS_X 12
#define SPACE_BETWEEN_ENEMYS_Y 24

/**
 * @brief Tipos de animações possíveis para um inimigo.
 */
typedef enum {
	MOVING,                 /**< Inimigo movendo-se lateralmente. */
	DYING,                  /**< Inimigo foi destruído. */
	TOTAL_ENEMY_ANIMATIONS, /**< Quantidade de animações. */
} enemy_animations_t;

/**
 * @brief Direção de movimento global da horda.
 */
typedef enum {
	MOVING_RIGHT,
	MOVING_LEFT,
} movement_direction_t;

/**
 * @brief Nó de lista encadeada representando um inimigo.
 */
typedef struct enemy_obj
{
	object_t render_info;                 /**< Dados físicos e de sprite. */
	struct enemy_obj *prox;               /**< Próximo inimigo na mesma coluna. */
	enemy_animations_t animation_playing; /**< Estado atual da animação. */
	bool alive;                           /**< Define se o alien está vivo. */
} enemy_obj_t;

/**
 * @brief Lista encadeada representando uma coluna de inimigos.
 */
struct enemy_list
{
	enemy_obj_t *head; /**< Início da lista. */
};

/**
 * @brief Matriz que controla toda a horda de inimigos.
 */
struct enemy_grid
{
	enemy_list_t list[COLS_OF_ENEMYS];      /**< Array de listas (colunas). */
	int nenemys;                            /**< Total de inimigos vivos. */
	movement_direction_t move_direction;    /**< Direção atual. */
	unsigned int move_speed;                /**< Velocidade atual. */
	bullet_list_t *bullets;                 /**< Lista de tiros inimigos. */
};

/**
 * @brief Inicializa a cabeça de uma lista de inimigos (coluna).
 * @param list Ponteiro para a lista a ser inicializada.
 */
void init_enemy_list(enemy_list_t *list);

/**
 * @brief Instancia a matriz de inimigos inicial.
 * @param gs Estado do jogo.
 */
void create_enemy_grid(game_state_t *gs);

/**
 * @brief Cria e insere um novo inimigo em uma coluna específica.
 * @param render Contexto SDL_Renderer.
 * @param list Coluna para inserção.
 * @param wich_col Índice da coluna (para cálculo de posição).
 */
void create_enemy(SDL_Renderer *render, enemy_list_t *list, int wich_col);

/**
 * @brief Atualiza física, colisão e disparo dos inimigos.
 * @param gs Estado do jogo.
 */
void update_enemys(game_state_t *gs);

/**
 * @brief Renderiza os Inimigos na Tela.
 * @param gs Estado do jogo. */
void render_enemy_current_state(game_state_t *gs);

#endif
