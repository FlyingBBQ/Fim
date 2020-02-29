#pragma once

#include "level.h"
#include "sprites.h"

/* size of a map */
#define MAP_SIZE 16

enum Flags {
        F_BORDER   = (1 << 0),
        F_SOLUTION = (1 << 1),
        F_FINISH   = (1 << 2)
};

typedef struct {
        int x;
        int y;
        int type;
        unsigned char flags;
} Tiles;

typedef struct {
        Tiles tiles[MAP_SIZE][MAP_SIZE];
        Pos fim;
        int offset;
} Map;

void map_new(void);
Map *map_get(void);

bool has_flag(Tiles *tile, unsigned char flags);
void set_flag(Tiles *tile, int flags);
void unset_flag(Tiles *tile, int flags);
