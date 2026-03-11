/**
 * @file bullet.h
 * @brief Gerenciamento dos projéteis (balas) utilizando listas duplamente encadeadas.
 */

#ifndef _BULET_H
#define _BULET_H

#include "objects.h"
#include "game_state.h"
#include "SDL2/SDL_image.h"

/**
 * @brief Nó da lista duplamente encadeada representando uma bala.
 */
typedef struct bullet_obj
{
	object_t render_info;      /**< Informações de física e renderização da bala. */
	struct bullet_obj *prox;   /**< Ponteiro para a próxima bala. */
	struct bullet_obj *ant;    /**< Ponteiro para a bala anterior. */
} bullet_obj_t;

/**
 * @brief Estrutura da lista duplamente encadeada de balas.
 */
struct bullet_list
{
	bullet_obj_t *head;        /**< Início da lista. */
	bullet_obj_t *tail;        /**< Final da lista. */

	int nbullets;              /**< Quantidade atual de balas ativas. */
	float couldown;            /**< Tempo de recarga restante para o próximo tiro. */
	int move_speed;            /**< Velocidade de deslocamento da bala. */

	object_type_t owner;       /**< Tipo de dono da bala (PLAYER ou ENEMY). */
};

/**
 * @brief Aloca e inicializa uma nova lista de balas.
 * @param owner Dono da lista (PLAYER ou ENEMY).
 * @return Ponteiro para a lista recém criada.
 */
bullet_list_t *initialize_bullet_list(object_type_t owner);

/**
 * @brief Cria uma nova bala e a insere na lista, se o cooldown permitir.
 * @param render Contexto do renderizador SDL.
 * @param gs Estado do jogo.
 * @param bullet_list Lista alvo para inserir a bala.
 */
void create_bullet(SDL_Renderer *render, game_state_t* gs, bullet_list_t* bullet_list);

/**
 * @brief Atualiza a física de todas as balas ativas.
 * @param gs Estado do jogo.
 */
void update_bullets(game_state_t *gs);

/**
 * @brief Renderiza as balas na Tela.
 * @param gs Estado do jogo. */
void render_bullets_current_state(game_state_t *gs);
#endif
