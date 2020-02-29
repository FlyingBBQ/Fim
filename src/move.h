#pragma once

#include "map.h"

#include <stdbool.h>

typedef enum {
        NORTH,
        EAST,
        SOUTH,
        WEST
} Way;

Way move_opposite(Way way);
bool move_position(Pos *fim, Way way);
void move_position_multiple(Pos *fim, Way way, unsigned int steps);
int move_check_free_space(Map map, Way way);
