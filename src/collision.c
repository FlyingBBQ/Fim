#include "collision.h"

// return the row
int getRow(int id)
{
    return (int)id / LEVELSIZE;
}

// return the column
int getCol(int id)
{
    return (int)id % LEVELSIZE;
}

// calculate space from current position to next collision
int rowSpace(int id, int dir)
{
    int space = 0;
    // for row: direction is either EAST or WEST
    switch (dir)
    {
        case EAST:
            // traverse from the current position in the row to the end
            for (int row = id; row < (getRow(id) * LEVELSIZE + LEVELSIZE); row++)
            {
                // if either a border or tile is encountered break and return space
                if (toTales[row].border == TRUE || toTales[row].type == TEX_grass)
                {
                    space = (row - id) - 1;
                    break;
                }
            }
            break;
        case WEST:
            for (int row = id; row >= (getRow(id) * LEVELSIZE); row--)
            {
                if (toTales[row].border == TRUE || toTales[row].type == TEX_grass)
                {
                    space = (id - row) - 1;
                    break;
                }
            }
            break;
    }
    return space;
}

int colSpace(int id, int dir)
{
    int space = 0;
    switch (dir)
    {
        case NORTH:
            for (int col = id; col > 0; col -= LEVELSIZE)
            {
                if (toTales[col].border == TRUE || toTales[col].type == TEX_grass)
                {
                    space = ((id - col) / LEVELSIZE) - 1;
                    break;
                }
            }
            break;
        case SOUTH:
            for (int col = id; col < (TILES); col += LEVELSIZE)
            {
                if (toTales[col].border == TRUE || toTales[col].type == TEX_grass)
                {
                    space = ((col - id) / LEVELSIZE) - 1;
                    break;
                }
            }
            break;
    }
    return space;
}


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
        if (dir == -1 && (toTales[col].border == TRUE || toTales[col].type == type))
        {
            collisionID = col;
        }
    }
    return collisionID;
}
