#include "level.h"

#include <stdlib.h>
#include <string.h>

static unsigned int g_solution[SOLUTION_SIZE];

Direction
opposite_direction(Direction const dir)
{
        return (dir + 2) % 4;
}

static void
level_generate_solution(unsigned int solution[])
{
        /* The first direction can be anywhere */
        solution[0] = (unsigned int)rand() % 4u;
        for (unsigned int i = 1; i < SOLUTION_SIZE; ++i) {
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

void
level_new_solution(void)
{
        memset(g_solution, 0, sizeof(g_solution));
        level_generate_solution(g_solution);
}

unsigned int const *
level_get_solution(void)
{
        return g_solution;
}
