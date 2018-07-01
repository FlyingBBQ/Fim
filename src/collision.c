#include "collision.h"

/* basic directional movement function */
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
    if (pos > TOTAL_TILES)
    {
        printf("movePos OOB\n");
        return 0;
    }
    else
    {
        return pos;
    }
}

/* helper functions */
int getType(int pos)
{
    return toTales[pos].type;
}

bool isBorder(int pos)
{
    return toTales[pos].border;
}

bool isSolution(int pos)
{
    return toTales[pos].solution;
}

/*
 * Multiple collision check function
 * returns true if any of type, border or solution returns true
 */
bool isCollision(int pos, int type, bool border, bool solution)
{
    if (type == getType(pos))
        return true;

    else if (border && isBorder(pos))
        return true;

    else if (solution && isSolution(pos))
        return true;

    else
        return false;
}

/* returns the available spaces in direction while not hitting grass or border */
int moveSpace(int pos, int dir)
{
    int space = 0;
    while (!isCollision(movePos(pos, dir, 1), TEX_grass, true, false))
    {
        pos = movePos(pos, dir, 1);
        space++;
    }
    return space;
}

/* return the row */
int getRow(int id)
{
    return (int)id / LEVELSIZE;
}

/* return the column */
int getCol(int id)
{
    return (int)id % LEVELSIZE;
}
