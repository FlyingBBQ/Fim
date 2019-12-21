#include "sprites.h"

void
setClip( void )
{
        gClips[TEX_sprite].x = TILE_SIZE;
        gClips[TEX_sprite].y = 0;
        gClips[TEX_sprite].w = TILE_SIZE;
        gClips[TEX_sprite].h = TILE_SIZE;

        gClips[TEX_bg].x = 0;
        gClips[TEX_bg].y = 0;
        gClips[TEX_bg].w = TILE_SIZE;
        gClips[TEX_bg].h = TILE_SIZE;

        gClips[TEX_grass].x = 0;
        gClips[TEX_grass].y = TILE_SIZE;
        gClips[TEX_grass].w = TILE_SIZE;
        gClips[TEX_grass].h = TILE_SIZE;

        gClips[TEX_water].x = TILE_SIZE;
        gClips[TEX_water].y = TILE_SIZE;
        gClips[TEX_water].w = TILE_SIZE;
        gClips[TEX_water].h = TILE_SIZE;
}
