#ifndef __SPACE_INVADERS_H
#define __SPACE_INVADERS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "objects.h"
#include "bullet.h"

#define WIDTH 640
#define HEIGHT 480

#define FRAMES 30
#define TICKS_PER_FRAME 1000/FRAMES

void render_game_objects (SDL_Renderer *render, Bullet_list *bullet_list, Objects*);

#endif

