#pragma once

#include <stdbool.h>
#include "map.h"

typedef enum {
        NORTH,
        EAST,
        SOUTH,
        WEST
} Way;

Way move_opposite(Way way);
bool move_position(Pos *fim, Way way);
int move_check_free_space(Map map, Way way);

void set_flag(Tiles *tile, int flags);
void unset_flag(Tiles *tile, int flags);
