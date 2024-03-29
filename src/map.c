#include "map.h"

#include "log.h"
#include "mem_leak_test.h"
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
        } else if (has_flag(tile, F_OBSTACLE)) {
                tile->type = TEX_grass;
        } else if (has_flag(tile, F_SOLUTION)) {
                tile->type = TEX_bg;
        } else {
                tile->type = TEX_bg;
        }
}

static void
map_generate_xy(Map * map)
{
        size_t const map_size = map->map_size;
        Tiles ** tiles = map->tiles;
        int clip_x = 0;
        int clip_y = 0;

        for (size_t x = 0; x < map_size; ++x) {
                for (size_t y = 0; y < map_size; ++y) {
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

        // Check if the first position in the solution is odd.
        if (finish_dir & 1u) {
                // east || west
                map->player.x = (EAST == finish_dir) ? (map_size - 1) : 0;
                map->player.y = finish_pos;
        } else {
                // north || south
                map->player.y = (NORTH == finish_dir) ? 0 : (map_size - 1);
                map->player.x = finish_pos;
        }
        set_flag(&map->tiles[map->player.x][map->player.y], F_FINISH);
}

void
map_generate_random_obstacles(Map * map, int nr_of_obstacles)
{
        int const map_size = (int)map->map_size;
        if (nr_of_obstacles > map_size) {
                nr_of_obstacles = map_size;
        }
        for (int i = 0; i < nr_of_obstacles; ++i) {
                int tile_to_mark = rand() % (map_size * map_size);
                int x = tile_to_mark / map_size;
                int y = tile_to_mark % map_size;
                Tiles * tile = &map->tiles[x][y];
                if (!has_flag(tile, (F_SOLUTION | F_FINISH))) {
                        set_flag(tile, F_OBSTACLE);
                }
        }
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
                        free(tiles);
                        return NULL;
                }
        }
        return tiles;
}

static void
tiles_clean(Tiles ** tiles, size_t const map_size)
{
        if (tiles == NULL) {
                return;
        }
        for (size_t i = 0; i < map_size; ++i) {
                free(tiles[i]);
        }
        free(tiles);
}

Map *
map_new(size_t const map_size, Direction const finish_dir, Pos const offset)
{
        Map * map = malloc(sizeof(Map));
        if (map == NULL) {
                LOG_ERROR("Failed to allocate memory for map");
                return NULL;
        }
        memset(map, 0, sizeof(Map));
        map->finished = false;
        map->offset = offset;
        map->map_size = map_size;
        map->tiles = tiles_new(map_size);
        if (map->tiles == NULL) {
                LOG_ERROR("Failed to allocate memory for map tiles");
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
        if (map == NULL) {
                return;
        }
        tiles_clean(map->tiles, map->map_size);
        free(map);
}
