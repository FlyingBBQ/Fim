#pragma once

#include "SDL2/SDL.h"

/* texture size per tile */
#define TILE_SIZE 16

/* total sprites taken from single texture */
#define MAX_SPRITES 4

enum Textures {
        TEX_sprite,
        TEX_bg,
        TEX_grass,
        TEX_water
};

extern SDL_Rect sprite_clips[MAX_SPRITES];

void sprites_set_clip(void);
