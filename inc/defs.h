#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/* texture size per tile */
#define TILESIZE 16

/* size of level in tiles for 1 side */
#define LEVELSIZE 16

/* total amount of tiles per level */
#define TOTAL_TILES (LEVELSIZE * LEVELSIZE)

/* solution size */
#define SOLSIZE 8

#define SCREEN_WIDTH (TILESIZE*LEVELSIZE)
#define SCREEN_HEIGHT (TILESIZE*LEVELSIZE)

/* total sprites taken from single texture */
#define MAX_SPRITES 4

/* boolean compatible with C89 */
typedef enum { false, true } bool;

enum
{
    TEX_sprite,
    TEX_bg,
    TEX_grass,
    TEX_water
};

enum
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

