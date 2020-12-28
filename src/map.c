#include "map.h"

#include <stdbool.h>
#include <stddef.h>

bool
has_flag(Tiles const * tile, unsigned int const flags)
{
        return (tile->flags & flags);
}

void
set_flag(Tiles * tile, unsigned int const flags)
{
        tile->flags |= flags;
}

void
unset_flag(Tiles * tile, unsigned int const flags)
{
        tile->flags &= ~flags;
}

Direction
opposite_direction(Direction const dir)
{
        return (dir + 2) % 4;
}

void
map_set_tile_type(Tiles * tile)
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
map_generate_xy(Map * map)
{
        int const map_size = (int)map->map_size;
        Tiles ** tiles = map->tiles;
        int clip_x = 0;
        int clip_y = 0;

        for (int x = 0; x < map_size; ++x) {
                for (int y = 0; y < map_size; ++y) {
                        tiles[x][y].x = clip_x;
                        tiles[x][y].y = clip_y;
                        clip_y += TILE_SIZE;
                }
                clip_x += TILE_SIZE;
                clip_y = 0;
        }
}

static void
map_set_finish_tile(Map * map, Direction const finish_dir)
{
        int const map_size = (int)map->map_size;
        int finish_pos = rand() % map_size;

        /* Check if the first position in the solution is odd */
        if (finish_dir & 1u) {
                /* east || west */
                map->player.x = (EAST == finish_dir) ? (map_size - 1) : 0;
                map->player.y = finish_pos;
        } else {
                /* north || south */
                map->player.y = (NORTH == finish_dir) ? 0 : (map_size - 1);
                map->player.x = finish_pos;
        }
        set_flag(&map->tiles[map->player.x][map->player.y], F_FINISH);
}

static Tiles **
tiles_new(size_t const map_size)
{
        Tiles ** tiles = calloc(map_size, sizeof(Tiles *));
        if (tiles == NULL) {
                return NULL;
        }
        for (size_t i = 0; i < map_size; ++i) {
                tiles[i] = calloc(map_size, sizeof(Tiles));
                if (tiles[i] == NULL) {
                        return NULL;
                }
        }
        return tiles;
}

void
tiles_clean(Tiles ** tiles, size_t const map_size)
{
        for (size_t i = 0; i < map_size; ++i) {
                free(tiles[i]);
        }
        free(tiles);
}

Map *
map_new(size_t const map_size, Direction const finish_dir)
{
        Map * map = malloc(sizeof(Map));
        if (map == NULL) {
                puts("Failed to allocate memory for map");
                return NULL;
        }
        memset(map, 0, sizeof(Map));
        map->offset = 0;
        map->map_size = map_size;
        map->tiles = tiles_new(map_size);
        if (map->tiles == NULL) {
                puts("Failed to allocate memory for map tiles");
                free(map);
                return NULL;
        }
        map_set_finish_tile(map, finish_dir);
        map_generate_xy(map);
        return map;
}

void
map_clean(Map * map)
{
        tiles_clean(map->tiles, map->map_size);
        free(map);
}
