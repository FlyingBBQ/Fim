#pragma once

#include "map.h"

#include <stdbool.h>

typedef enum {
        NORTH,
        EAST,
        SOUTH,
        WEST
} Way;

Way move_opposite(Way const way);
bool move_position(Pos *fim, Way const way);
void move_position_multiple(Pos *fim, Way const way, unsigned int const steps);
unsigned int move_check_free_space(Map map, Way const way);
unsigned int move_get_collision(Map map, Way const way);
void move_to_way(Map *map, Way const way);
