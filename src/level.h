#pragma once

#include "player.h"

#define SOLUTION_SIZE 8

typedef enum {
        NORTH,
        EAST,
        SOUTH,
        WEST
} Direction;

Direction opposite_direction(Direction const dir);
void level_new_solution(void);
unsigned int const *level_get_solution(void);
