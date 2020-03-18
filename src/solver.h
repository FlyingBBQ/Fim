#pragma once

#include "move.h"

void solver_step(Map *map, Direction const dir);
void solver_step_multiple(Map *map, unsigned int const solution_steps);
bool solver_sanity_check(unsigned int const solution_steps);
