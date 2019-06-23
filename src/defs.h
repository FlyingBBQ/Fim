#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

/* texture size per tile */
#define TILE_SIZE 16

/* size of level in tiles for 1 side */
#define LEVELSIZE 28

/* total amount of tiles per level */
#define TOTAL_TILES (LEVELSIZE * LEVELSIZE)

/* solution size */
#define SOLSIZE 12

#define SCREEN_WIDTH (TILE_SIZE*LEVELSIZE)
#define SCREEN_HEIGHT (TILE_SIZE*LEVELSIZE)

/* total sprites taken from single texture */
#define MAX_SPRITES 4

/* size of a map */
#define MAP_SIZE 16

enum
{
    TEX_sprite,
    TEX_bg,
    TEX_grass,
    TEX_water
};

typedef enum
{
    NORTH,
    EAST,
    SOUTH,
    WEST
} WAY;

enum Flags
{
        F_BORDER   = (1 << 0),
        F_SOLUTION = (1 << 1)
};
