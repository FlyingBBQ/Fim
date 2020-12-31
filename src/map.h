#pragma once

#include "player.h"
#include "sprites.h"

/* size of a map */
#define MAP_SIZE 16

enum Flags {
        F_OBSTACLE = (1 << 0),
        F_SOLUTION = (1 << 1),
        F_FINISH   = (1 << 2)
};

typedef enum {
        NORTH,
        EAST,
        SOUTH,
        WEST
} Direction;

typedef struct {
        int x;
        int y;
        int type;
        unsigned int flags;
} Tiles;

typedef struct {
        Pos player;
        int offset;
        size_t map_size;
        Tiles ** tiles;
} Map;

Map * map_new(size_t const map_size, Direction const finish_dir);
void map_clean(Map * map);

Direction opposite_direction(Direction const dir);

bool has_flag(Tiles const * tile, unsigned int const flags);
void set_flag(Tiles * tile, unsigned int const flags);
void unset_flag(Tiles * tile, unsigned int const flags);
void map_set_tile_type(Tiles * tile);
void map_generate_random_obstacles(Map * map, int nr_of_obstacles);
