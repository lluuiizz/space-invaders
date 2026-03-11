/**
 * @file space_invaders.h
 * @brief Constantes gerais do jogo
 */

#ifndef __SPACE_INVADERS_H
#define __SPACE_INVADERS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "game_state.h"
#include "objects.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

#define WIDTH 640   /**< Largura da janela do jogo. */
#define HEIGHT 480  /**< Altura da janela do jogo. */

#define FRAMES 24   /**< Taxa de quadros alvo (FPS). */
#define TICKS_PER_FRAME 1000/FRAMES /**< Tempo em milissegundos para manter o FPS. */

#endif
