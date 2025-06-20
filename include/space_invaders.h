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

#define WIDTH 640
#define HEIGHT 480

#define FRAMES 24
#define TICKS_PER_FRAME 1000/FRAMES

void render_game_objects (SDL_Renderer *render, game_state_t*);

#endif

