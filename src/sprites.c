#include "sprites.h"

void setClip( void )
{
    gClips[TEX_sprite].x = TILESIZE;
    gClips[TEX_sprite].y = 0;
    gClips[TEX_sprite].w = TILESIZE;
    gClips[TEX_sprite].h = TILESIZE;
    
    gClips[TEX_bg].x = 0;
    gClips[TEX_bg].y = 0;
    gClips[TEX_bg].w = TILESIZE;
    gClips[TEX_bg].h = TILESIZE;

    gClips[TEX_grass].x = 0;
    gClips[TEX_grass].y = TILESIZE;
    gClips[TEX_grass].w = TILESIZE;
    gClips[TEX_grass].h = TILESIZE;

    gClips[TEX_water].x = TILESIZE;
    gClips[TEX_water].y = TILESIZE;
    gClips[TEX_water].w = TILESIZE;
    gClips[TEX_water].h = TILESIZE;
}
