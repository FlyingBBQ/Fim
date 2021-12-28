#include "level.h"

#include "log.h"
#include "map.h"
#include "mem_leak_test.h"
#include "solver.h"
#include <stdlib.h>
#include <string.h>

#define MAX_RETRIES 4

static void
generate_solution(unsigned int * solution, size_t const solution_size)
{
        // The first direction can be anywhere.
        solution[0] = (unsigned int)rand() % 4u;
        for (unsigned int i = 1; i < solution_size; ++i) {
                unsigned int r;
                bool invalid_direction;
                do {
                        r = (unsigned int)rand() % 4;
                        invalid_direction = (r == opposite_direction(solution[i - 1]));
                        // Re-roll if an invalid solution is generated.
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

static Pos
calculate_map_offset(size_t const map, size_t const map_size,
                     size_t const nr_of_maps)
{
        Pos offset_pos = {0};
        int offset_pixels = (int)((map_size * TILE_SIZE) + map_size);

        if (nr_of_maps <= 4) {
                if (map == 1) {
                        offset_pos.x = offset_pixels;
                }
                if (map == 2) {
                        offset_pos.y = offset_pixels;
                }
                if (map == 3) {
                        offset_pos.x = offset_pixels;
                        offset_pos.y = offset_pixels;
                }
        }
        return offset_pos;
}

static Map **
create_maps(size_t const nr_of_maps, size_t const map_size,
            unsigned int const * solution, size_t const solution_size)
{
        // Create the array of maps.
        Map ** maps = calloc(nr_of_maps, sizeof(Map *));
        if (maps == NULL) {
                return NULL;
        }
        // Initialize and test each map for solvability.
        for (size_t i = 0; i < nr_of_maps; ++i) {
                bool solvable = false;
                unsigned int tries = MAX_RETRIES;
                Pos offset = calculate_map_offset(i, map_size, nr_of_maps);
                do {
                        maps[i] = map_new(map_size, solution[0], offset);
                        if (maps[i] != NULL) {
                                solver_solve_map(maps[i], solution, solution_size);
                                // TODO: able to 'toggle' random obstacles.
                                map_generate_random_obstacles(maps[i], (int)solution_size);
                                solvable = solver_is_solvable(*maps[i], solution, solution_size);
                        }
                        if (!solvable) {
                                map_clean(maps[i]);
                                maps[i] = NULL;
                        }
                } while (!solvable && --tries);

                if (tries == 0) {
                        LOG_DEBUG("Failed %i times to solve map %li", MAX_RETRIES, i);
                        while (i > 0) {
                                map_clean(maps[--i]);
                        }
                        free(maps);
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
                LOG_ERROR("Failed to allocate memory for level");
                return NULL;
        }
        level->solution = new_solution(solution_size);
        if (level->solution == NULL) {
                LOG_ERROR("Failed to allocate memory for solution.");
                free(level);
                return NULL;
        }
        level->maps = create_maps(nr_of_maps, map_size, level->solution, solution_size);
        if (level->maps == NULL) {
                LOG_DEBUG("Failed to create maps.");
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

bool
level_is_finished(Level * level)
{
        bool finished = false;
        unsigned int maps_finished = 0;

        if (player_is_quitting()) {
                return true;
        }

        for (unsigned int i = 0; i < level->nr_of_maps; ++i) {
                maps_finished += level->maps[i]->finished ? 1 : 0;
        }
        if (maps_finished == level->nr_of_maps) {
                finished = true;
        }
        return finished;
}
