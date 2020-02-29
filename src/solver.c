#include "solver.h"

#include <assert.h>

static void
solver_prepare_step(Map *map, Way const way)
{
        Pos fim = map->fim;

        if (move_position(&fim, way)) {
                set_flag(&map->tiles[fim.x][fim.y], F_BORDER);
        } else {
                puts("failed to prepare");
        }
}

void
solver_step(Map *map, Way const way)
{
        unsigned int free_space = move_check_free_space(*map, move_opposite(way));
        unsigned int steps = free_space ? (rand() % free_space) : 0;

        move_position_multiple(&map->fim, move_opposite(way), steps);
}

void
solver_step_multiple(Map *map, unsigned int const solution_steps)
{
        assert(solution_steps <= SOLUTION_SIZE);

        unsigned int const *solution = level_get_solution();

        /* The first step is already prepared */
        solver_step(map, solution[0]);
        for (unsigned int i = 1; i < solution_steps; ++i) {
                solver_prepare_step(map, solution[i]);
                solver_step(map, solution[i]);
        }
}

bool
solver_sanity_check(unsigned int const solution_steps)
{
        assert(solution_steps <= SOLUTION_SIZE);

        bool solvable = false;
        unsigned int const *solution = level_get_solution();
        /* get a local copy of the map to not overwrite the actual pos */
        Map map = *map_get();

        for (unsigned int i = solution_steps - 1; i < SOLUTION_SIZE; --i) {
                move_to_way(&map, solution[i]);
                if (move_get_collision(map, solution[i]) & F_FINISH) {
                        puts("solvable");
                        solvable = true;
                }
        }
        //assert(solvable);
        if (!solvable) {
                puts("not solvable");
        }
        return solvable;
}
