#include "defs.h"

typedef struct Entity {
    SDL_Texture *iTexture;
    int xpos, ypos;
    int iWidth, iHeight;
} Entity;

typedef struct Player {
    int prev, pos;
    int moves;
} Player;



typedef struct {
        int x;
        int y;
        int type;
        unsigned char flags;
} Tiles;

typedef struct {
        int x;
        int y;
} Pos;

typedef struct {
        Tiles tiles[MAP_SIZE][MAP_SIZE];
        Pos fim;
        int offset;
} Map;
