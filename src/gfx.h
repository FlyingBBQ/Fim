#pragma once

#include "map.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#define SCREEN_WIDTH    528
#define SCREEN_HEIGHT   528

void gfx_init(char * title);
void gfx_cleanup(void);
void gfx_render(int x, int y, SDL_Rect * clip);
void gfx_render_player(Map * map);
SDL_Renderer * gfx_get_renderer(void);
void gfx_draw(Map * map);

