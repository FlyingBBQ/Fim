#include "collision.h"

// basic directional movement function
int movePos(int pos, int dir, int steps)
{
    switch (dir)
    {
        case NORTH:
            pos -= steps * LEVELSIZE;
            break;
        case EAST:
            pos += steps;
            break;
        case SOUTH:
            pos += steps * LEVELSIZE;
            break;
        case WEST:
            pos -= steps;
            break;
    }
    return pos;
}

// helper functions
int getType(int pos)
{
    return toTales[pos].type;
}

int isBorder(int pos)
{
    return toTales[pos].border;
}

int isSolution(int pos)
{
    return toTales[pos].solution;
}

// Multiple collision check function
// returns TRUE if any of type, border or solution returns TRUE
int isCollision(int pos, int type, int border, int solution)
{
    if (type == getType(pos))
    {
        return TRUE;
    }
    else if (border && isBorder(pos))
    {
        return TRUE;
    }
    else if (solution && isSolution(pos))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

// returns the available spaces in direction while not hitting grass or border
int moveSpace(int pos, int dir)
{
    int space = 0;
    while (!isCollision(movePos(pos, dir, 1), TEX_grass, TRUE, FALSE))
    {
        pos = movePos(pos, dir, 1);
        space++;
    }
    return space;
}

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
