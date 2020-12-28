#pragma once

#include "move.h"

void solver_step(Map * map, Direction const dir);
bool solver_initialize(Map * map, Direction const finish_dir);
void solver_step_multiple(Map * map, unsigned int const * solution,
                          size_t const solution_size);
bool solver_sanity_check(Map * map, unsigned int const * solution,
                         size_t const solution_size);
bool solver_run(Map * map, unsigned int const * solution,
                size_t const solution_size);
