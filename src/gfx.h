#pragma once

#include "map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define FONT_SIZE       18
#define SCREEN_WIDTH    (512 + TILE_SIZE)
#define SCREEN_HEIGHT   (SCREEN_WIDTH + FONT_SIZE)

void gfx_init(char * title);
void gfx_cleanup(void);
void gfx_draw_player(Map * map);
void gfx_draw_map(Map * map);
void gfx_draw_text(char * text, int x, int y);
SDL_Renderer * gfx_get_renderer(void);

