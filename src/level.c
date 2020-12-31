#include "level.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "solver.h"

#define MAX_RETRIES 4

static void
generate_solution(unsigned int * solution, size_t const solution_size)
{
        /* The first direction can be anywhere */
        solution[0] = (unsigned int)rand() % 4u;
        for (unsigned int i = 1; i < solution_size; ++i) {
                unsigned int r;
                bool invalid_direction;
                do {
                        r = (unsigned int)rand() % 4;
                        invalid_direction = (r == opposite_direction(solution[i - 1]));
                        /* Re-roll if an invalid solution is generated */
                } while (invalid_direction);
                solution[i] = r;
        }
}

static unsigned int const *
new_solution(size_t const solution_size)
{
        unsigned int * solution = malloc(solution_size * sizeof(unsigned int));
        if (solution == NULL) {
                return NULL;
        }
        generate_solution(solution, solution_size);
        return solution;
}

static Map **
create_maps(size_t const nr_of_maps, size_t const map_size,
            unsigned int const * solution, size_t const solution_size)
{
        /* Create the array of maps */
        Map ** maps = calloc(nr_of_maps, sizeof(Map *));
        if (maps == NULL) {
                return NULL;
        }
        /* Initialize and test each map for solvability */
        for (size_t i = 0; i < nr_of_maps; ++i) {
                bool solvable = false;
                unsigned int tries = MAX_RETRIES;
                int offset = (int)((map_size * TILE_SIZE) + map_size);
                do {
                        maps[i] = map_new(map_size, solution[0], (i == 1) ? offset : 0);
                        if (maps[i] == NULL) {
                                continue;
                        }
                        solvable = solver_run(maps[i], solution, solution_size);
                        if (!solvable) {
                                map_clean(maps[i]);
                        }
                } while (!solvable && --tries);

                if (tries == 0) {
                        printf("Failed %i times to solve map, create new solution\n", MAX_RETRIES);
                        maps = NULL;
                        break;
                }
        }
        return maps;
}

Level *
level_new(size_t const solution_size, size_t const nr_of_maps,
          size_t const map_size)
{
        Level * level = malloc(sizeof(Level));
        if (level == NULL) {
                puts("Failed to allocate memory for level");
                return NULL;
        }
        level->solution = new_solution(solution_size);
        if (level->solution == NULL) {
                puts("Failed to allocate memory for solution.");
                free(level);
                return NULL;
        }
        level->maps = create_maps(nr_of_maps, map_size, level->solution, solution_size);
        if (level->maps == NULL) {
                puts("Failed to create maps.");
                free((void *)level->solution);
                free(level);
                return NULL;
        }
        level->solution_size = solution_size;
        level->nr_of_maps = nr_of_maps;
        return level;
}

void
level_clean(Level * level)
{
        if (level == NULL) {
                return;
        }
        free((void *)level->solution);
        for (size_t i = 0; i < level->nr_of_maps; ++i) {
                map_clean(level->maps[i]);
        }
        free(level->maps);
        free(level);
}
