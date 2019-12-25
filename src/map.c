#include "map.h"

static Map map = {0};

static void
map_generate_xy(Tiles tiles[MAP_SIZE][MAP_SIZE])
{
        int clip_x = 0;
        int clip_y = 0;

        for (int x = 0; x < MAP_SIZE; ++x) {
                for (int y = 0; y < MAP_SIZE; ++y) {
                        tiles[x][y].x = clip_x;
                        tiles[x][y].y = clip_y;
                        clip_y += TILE_SIZE;
                }
                clip_x += TILE_SIZE;
                clip_y = 0;
        }
}

void
map_new(void)
{
        map_generate_xy(map.tiles);
}

Map *
map_get(void)
{
        return &map;
}
