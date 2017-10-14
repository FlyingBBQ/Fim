#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define TILESIZE 16

#define MAX_SPRITES 4

enum 
{
    TEX_sprite,
    TEX_bg,
    TEX_grass,
    TEX_water,
};
