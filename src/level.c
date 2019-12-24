#include "level.h"

#include <stdlib.h>
#include <time.h>

//static int solution[SOLUTION_SIZE];

void
level_generate_solution(int *solution)
{
        srand(time(NULL));

        for (int i = 0; i < SOLUTION_SIZE; ++i) {
                solution[i] = rand() % 4;
        }
}

