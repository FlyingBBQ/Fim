#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define TILESIZE 16

#define SCREEN_WIDTH (TILESIZE*16)
#define SCREEN_HEIGHT (TILESIZE*16)

#define MAX_SPRITES 4

enum 
{
    TEX_sprite,
    TEX_bg,
    TEX_grass,
    TEX_water,
};
