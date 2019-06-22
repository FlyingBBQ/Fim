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

typedef struct Tiles {
        int x;
        int y;
        int type;
        int flags;
} Tiles;

typedef struct Pos {
        int x;
        int y;
} Pos;

typedef struct Map {
        Tiles tiles[MAP_SIZE][MAP_SIZE];
        Pos fim;
} Map;
