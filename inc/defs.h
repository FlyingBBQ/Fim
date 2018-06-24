#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

// texture size per tile
#define TILESIZE 16

// total amount of tiles per level
#define TILES 256

// size of level in tiles
#define LEVELSIZE 16

// solution size
#define SOLSIZE 8

#define SCREEN_WIDTH (TILESIZE*LEVELSIZE)
#define SCREEN_HEIGHT (TILESIZE*LEVELSIZE)

// total sprites taken from single texture
#define MAX_SPRITES 4

// start enums at 1 to have 'default' 0 state
enum
{
    TEX_sprite = 1,
    TEX_bg,
    TEX_grass,
    TEX_water
};

enum
{
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
};

// boolean for clarity
enum
{
    FALSE,
    TRUE
};
