#pragma once

#include "move.h"

void solver_step(Map *map, Way const way);
bool solver_sanity_check(unsigned int const solution_steps);
