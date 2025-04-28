#ifndef __ANIMATION_H_
#define __ANIMATION_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
	SDL_Texture *sprite_sheet;
	int frame_w;
	int frame_h;
	int frame_now;
	int total_frames;
	float time_per_frame;
	float time_since_last;
	bool is_looping;
} animation_t;

#endif 
