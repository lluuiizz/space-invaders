/**
 * @file animation.h
 * @brief Estruturas para o controle de animações.
 */

#ifndef __ANIMATION_H_
#define __ANIMATION_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

/**
 * @brief Estrutura que gerencia uma animação baseada em Sprite Sheet.
 */
typedef struct {
	SDL_Texture *sprite_sheet; /**< Textura contendo todos os quadros da animação. */
	int frame_w;               /**< Largura de um quadro individual. */
	int frame_h;               /**< Altura de um quadro individual. */
	int frame_now;             /**< Índice do quadro atual sendo exibido. */
	int total_frames;          /**< Quantidade total de quadros na animação. */
	float time_per_frame;      /**< Tempo de duração de cada quadro (em segundos). */
	float time_since_last;     /**< Tempo percorrido desde a última troca de quadro. */
	bool is_looping;           /**< Define se a animação deve repetir ao terminar. */
} animation_t;

#endif
