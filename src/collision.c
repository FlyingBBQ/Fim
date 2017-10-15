#include "collision.h"

int searchRow(int id, int dir, int type)
{
    //
    int collisionID = 0;
    for (int row = (int)id / LEVELSIZE; row < (row + LEVELSIZE); row++)
    {
        if (toTales[row].dir == dir && toTales[row].type == type)
        {
            collisionID = row;
        }
    }
    return collisionID;
}

int searchCol(int id, int dir, int type)
{
    //
    int collisionID = 0;
    for (int col = (int)id % LEVELSIZE; col < TILES; col += LEVELSIZE)
    {
        if (toTales[col].dir == dir && toTales[col].type == type)
        {
            collisionID = col;
        }
    }
    return collisionID;
}
