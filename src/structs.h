#include "defs.h"

typedef struct Entity
{
    SDL_Texture *iTexture;
    int xpos, ypos;
    int iWidth, iHeight;
} Entity;

typedef struct Tiles
{
    int type;
    int xT, yT;
} Tiles;
