#include "level.h"

#include <stdlib.h>
#include <string.h>

static unsigned int solution[SOLUTION_SIZE];

static void
level_generate_solution(unsigned int solution[])
{
        /* The first direction can be anywhere */
        solution[0] = rand() % 4;
        for (unsigned int i = 1; i < SOLUTION_SIZE; ++i) {
                unsigned int r;
                bool inverse_direction;
                do {
                        r = rand() % 4;
                        inverse_direction = (r == ((solution[i - 1] + 2) % 4));
                        /* Re-roll if an invalid solution is generated */
                } while (inverse_direction);
                solution[i] = r;
        }
}

void
level_new_solution(void)
{
        memset(solution, 0, sizeof(solution));
        level_generate_solution(solution);
}

unsigned int const *
level_get_solution(void)
{
        return solution;
}
