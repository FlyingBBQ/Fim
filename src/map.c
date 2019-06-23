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

void
genMap(Tiles tiles[MAP_SIZE][MAP_SIZE])
{
        int xClip = 0;
        int yClip = 0;

        for (int x = 0; x < MAP_SIZE; x++) 
        {
                for (int y = 0; y < MAP_SIZE; y++)
                {
                        tiles[x][y].x = xClip;
                        tiles[x][y].y = yClip;

                        yClip += TILE_SIZE;
                }

                xClip += TILE_SIZE;
                yClip = 0;
        }

}
