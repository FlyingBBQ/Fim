#pragma once

#include "map.h"

#include <stdbool.h>

Direction opposite_direction(Direction const dir);
bool move_position(Pos *fim, Direction const dir);
void move_position_multiple(Pos *fim, Direction const dir, unsigned int const steps);
unsigned int move_check_free_space(Map map, Direction const dir);
unsigned int move_get_collision(Map map, Direction const dir);
void move_to_direction(Map *map, Direction const dir);
