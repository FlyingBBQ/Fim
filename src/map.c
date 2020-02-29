#include "map.h"

static Map map = {0};

bool
has_flag(Tiles *tile, unsigned char flags)
{
        return (tile->flags & flags);
}

void
set_flag(Tiles *tile, int flags)
{
        tile->flags |= flags;
}

void
unset_flag(Tiles *tile, int flags)
{
        tile->flags &= ~flags;
}

static void
map_set_tile_type(Tiles *tile)
{
        if (has_flag(tile, F_FINISH)) {
                tile->type = TEX_water;
        } else {
                tile->type = TEX_bg;
        }
}

static void
map_generate_xy(Tiles tiles[][MAP_SIZE])
{
        int clip_x = 0;
        int clip_y = 0;

        for (int x = 0; x < MAP_SIZE; ++x) {
                for (int y = 0; y < MAP_SIZE; ++y) {
                        tiles[x][y].x = clip_x;
                        tiles[x][y].y = clip_y;
                        map_set_tile_type(&tiles[x][y]);
                        clip_y += TILE_SIZE;
                }
                clip_x += TILE_SIZE;
                clip_y = 0;
        }
}

static void
map_set_finish_tile(Map *map)
{
        bool is_x = rand() % 2;
        bool is_start = rand() % 2;
        int finish_pos = rand() % MAP_SIZE;

        if (is_x) {
                map->fim.x = is_start ? 0 : (MAP_SIZE - 1);
                map->fim.y = finish_pos;
        } else {
                map->fim.y = is_start ? 0 : (MAP_SIZE - 1);
                map->fim.x = finish_pos;
        }
        set_flag(&map->tiles[map->fim.x][map->fim.y], F_FINISH);
}

void
map_new(void)
{
        level_new_solution();
        map_set_finish_tile(&map);
        map_generate_xy(map.tiles);
}

Map *
map_get(void)
{
        return &map;
}
