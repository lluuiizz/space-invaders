/**
 * @file objects.h
 * @brief Definições básicas de objetos e tipos renderizáveis do jogo.
 */

#ifndef __OBJECTS_H
#define __OBJECTS_H

#include <SDL2/SDL.h>
#include "animation.h"

/**
 * @brief Identificadores para os tipos de objetos no jogo.
 */
typedef enum
{
	PLAYER,           /**< Entidade do jogador. */
	ENEMY,            /**< Entidade inimiga (alien). */
	BULLET,           /**< Projétil. */
	N_OBJECTS_TYPES,  /**< Total de tipos de objetos. */
} object_type_t;

/**
 * @brief Estrutura base de renderização e colisão para os objetos do jogo.
 */
typedef struct
{
	union {
		SDL_Texture* sprite;     /**< Textura estática para objetos sem animação. */
		animation_t* animation;  /**< Array de animações para objetos animados. */
	};

	float		 pos_x, pos_y;   /**< Coordenadas exatas float (física). */
	SDL_Rect	 box;	         /**< Caixa delimitadora inteira (colisão e renderização). */

} object_t;

/* Declarações antecipadas (Forward declarations) para evitar dependência circular */
typedef struct player player_t;
typedef struct enemy_list enemy_list_t;
typedef struct enemy_grid enemy_grid_t;
typedef struct bullet_list bullet_list_t;

#endif
