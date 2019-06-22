#include "map.h"

WAY
oppositeWay(WAY way)
{
        return (way + 2) % 4;
}

void
genSolution(int *solution)
{
        srand(time(NULL));

        for (int i = 0; i < SOLUTION_SIZE; i++)
        {
                solution[i] = rand() % 4;
        }
}
