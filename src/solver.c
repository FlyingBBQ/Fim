#include "solver.h"

void
solver_step(Map *map, Way way)
{
        unsigned int free_space = 0;
        unsigned int steps = 0;

        free_space = move_check_free_space(*map, move_opposite(way));
        if (free_space) {
                steps = rand() % free_space;
        }
        move_position_multiple(&map->fim, move_opposite(way), steps);
}

void
solver_step_solution(Map *map)
{
        unsigned int const *solution = level_get_solution();

        for (unsigned int i = 0; i < SOLUTION_SIZE; ++i) {
                solver_step(map, solution[i]);
        }
}
