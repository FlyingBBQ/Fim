#include "map.h"

static const Map g_empty_map = {0};
static Map g_map;

bool
has_flag(Tiles const *tile, unsigned int const flags)
{
        return (tile->flags & flags);
}

void
set_flag(Tiles *tile, unsigned int const flags)
{
        tile->flags |= flags;
}

void
unset_flag(Tiles *tile, unsigned int const flags)
{
        tile->flags &= ~flags;
}

void
map_set_tile_type(Tiles *tile)
{
        if (has_flag(tile, F_FINISH)) {
                tile->type = TEX_water;
        } else if (has_flag(tile, F_BORDER)) {
                tile->type = TEX_grass;
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
                        clip_y += TILE_SIZE;
                }
                clip_x += TILE_SIZE;
                clip_y = 0;
        }
}

static void
map_set_finish_tile(Map *map, unsigned int const solution[])
{
        int finish_pos = rand() % MAP_SIZE;

        /* Check if the first position in the solution is odd */
        if (solution[0] & 1u) {
                /* east || west */
                map->player.x = (EAST == solution[0]) ? (MAP_SIZE - 1) : 0;
                map->player.y = finish_pos;
        } else {
                /* north || south */
                map->player.y = (NORTH == solution[0]) ? 0 : (MAP_SIZE - 1);
                map->player.x = finish_pos;
        }
        set_flag(&map->tiles[map->player.x][map->player.y], F_FINISH);
}

void
map_new(void)
{
        level_new_solution();
        g_map = g_empty_map ;
        map_set_finish_tile(&g_map, level_get_solution());
        map_generate_xy(g_map.tiles);
}

Map *
map_get(void)
{
        return &g_map;
}
