#include "solver.h"

#include <assert.h>
#include "move.h"

static void
solver_prepare_step(Map * map, Direction const dir)
{
        if (move_position(map, dir)) {
                set_flag(&map->tiles[map->player.x][map->player.y], F_BORDER);
        } else {
                puts("failed to prepare");
        }
}

void
solver_step(Map * map, Direction const dir)
{
        unsigned int free_space = move_check_free_space(*map, opposite_direction(dir));
        unsigned int steps = free_space ? ((unsigned int)rand() % free_space) : 0;

        move_position_multiple(map, opposite_direction(dir), steps);
}

bool
solver_initialize(Map * map, Direction const finish_dir)
{
        return move_position(map, opposite_direction(finish_dir));
}

void
solver_step_multiple(Map * map, unsigned int const * solution,
                     size_t const solution_size)
{
        /* The first step is already prepared */
        solver_step(map, solution[0]);
        for (unsigned int i = 1; i < solution_size; ++i) {
                /* Do not prepare if the direction is the same as the previous */
                if (solution[i] != solution[i - 1]) {
                        solver_prepare_step(map, solution[i]);
                }
                solver_step(map, solution[i]);
        }
}

bool
solver_sanity_check(Map map_copy, unsigned int const * solution,
                    size_t const solution_size)
{
        bool solvable = false;

        for (size_t i = solution_size - 1; i < solution_size; --i) {
                move_in_direction(&map_copy, solution[i]);
                if (move_get_collision(map_copy, solution[i]) & F_FINISH) {
                        solvable = true;
                        break;
                }
        }
        return solvable;
}

bool
solver_run(Map * map, unsigned int const * solution, size_t const solution_size)
{
        solver_initialize(map, solution[0]);
        solver_step_multiple(map, solution, solution_size);
        return solver_sanity_check(*map, solution, solution_size);
}
