#pragma once

#include "map.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   480

void gfx_init(char *title);
void gfx_cleanup(void);
void gfx_render(int x, int y, SDL_Rect *clip);
SDL_Renderer *gfx_get_renderer(void);
void gfx_draw(Map *map);

