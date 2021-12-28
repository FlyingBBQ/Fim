#pragma once

#include "move.h"

void solver_solve_map(Map * map, unsigned int const * solution,
                      size_t const solution_size);
bool solver_is_solvable(Map map_copy, unsigned int const * solution,
                        size_t const solution_size);
