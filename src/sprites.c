#include "sprites.h"

// The array containing the clip of each sprite.
SDL_Rect sprite_clips[MAX_SPRITES];

void
sprites_set_clip(void)
{
        sprite_clips[TEX_sprite].x = TILE_SIZE;
        sprite_clips[TEX_sprite].y = 0;
        sprite_clips[TEX_sprite].w = TILE_SIZE;
        sprite_clips[TEX_sprite].h = TILE_SIZE;

        sprite_clips[TEX_bg].x = 0;
        sprite_clips[TEX_bg].y = 0;
        sprite_clips[TEX_bg].w = TILE_SIZE;
        sprite_clips[TEX_bg].h = TILE_SIZE;

        sprite_clips[TEX_grass].x = 0;
        sprite_clips[TEX_grass].y = TILE_SIZE;
        sprite_clips[TEX_grass].w = TILE_SIZE;
        sprite_clips[TEX_grass].h = TILE_SIZE;

        sprite_clips[TEX_water].x = TILE_SIZE;
        sprite_clips[TEX_water].y = TILE_SIZE;
        sprite_clips[TEX_water].w = TILE_SIZE;
        sprite_clips[TEX_water].h = TILE_SIZE;
}
