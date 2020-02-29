#include "level.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

static unsigned int solution[SOLUTION_SIZE];

static void
level_generate_solution(unsigned int solution[])
{
        srand(time(NULL));

        for (int i = 0; i < SOLUTION_SIZE; ++i) {
                solution[i] = rand() % 4;
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
