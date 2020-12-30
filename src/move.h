#pragma once

#include "map.h"

Direction opposite_direction(Direction const dir);
bool move_position(Map * map, Direction const dir);
void move_position_multiple(Map * map, Direction const dir,
                            unsigned int const steps);
unsigned int move_check_free_space(Map map, Direction const dir);
unsigned int move_get_collision(Map map, Direction const dir);
void move_in_direction(Map * map, Direction const dir);
