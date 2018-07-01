#include "level.h"

int oppositeDir(int dir)
{
    return (dir + 2) % 4;
}

void printDir(int dir)
{
    switch (dir)
    {
        case NORTH:
            printf("N");
            break;
        case EAST:
            printf("E");
            break;
        case SOUTH:
            printf("S");
            break;
        case WEST:
            printf("W");
            break;
    }
}

void genSol(int dir)
{
    /* only call once to generate seed */
    srand(time(NULL));

    /* set the ending side */
    sol[0] = dir;
    printf("##############################");
    printf("\nsol: ");
    printDir(sol[0]);

    /* loop through the path */
    for(int i = 1; i < SOLSIZE; i++)
    {
        /* generate random number between 0-3 */
        int r = rand() % 4;
        while (r == oppositeDir(sol[i-1]) ||
              (i > 1 && (r == sol[i-1] && r == sol[i-2])))
        {
            r = rand() % 4;
        }

        /* assign a random direction for the solution path */
        switch (r)
        {
            case 0:
                sol[i] = NORTH;
                break;
            case 1:
                sol[i] = EAST;
                break;
            case 2:
                sol[i] = SOUTH;
                break;
            case 3:
                sol[i] = WEST;
                break;
        }
        printf("-");
        printDir(sol[i]);
    }
    printf("<--\n");
}

/* set TILE.solution true for the solution path */
int solPath(int pos, int dir, int steps)
{
    for (int i = 0; i < steps; i++)
    {
        toTales[movePos(pos, dir, 1)].solution = true;
        toTales[movePos(pos, dir, 1)].type = TEX_water;
        pos = movePos(pos, dir, 1);
    }
    return pos;
}

#if 0
/* calculate the next move */
int moveNext(int pos, int dir, int solCntr)
{
    /* check the available space in the direction */
    int space = moveSpace(pos, dir);

    //printf("space: %d\n", space);
    if (solCntr + 1 <= SOLSIZE && space > 0)
    {
        int tries = 6;
        for (int t = 0; t < tries; t++)
        {
            int steps = 1 + rand() % space;
            int tp = movePos(pos, dir, steps);
            if (!isSolution(movePos(tp, sol[solCntr + 1], 1)))
            {
                toTales[movePos(tp, sol[solCntr + 1], 1)].type = TEX_grass;
                return solPath(pos, dir, steps);
            }
            else if (t == tries - 1)
            {
                printf("failed\n");
            }
            printf("Retry: %d, dir: %d\n", steps, dir);
        }
    }
    return pos;
}
#endif

int bruteForce(int pos, int dir, int space, int solCntr)
{
    /* "brute force" for possible solution */
    printf("BRUTE");
    int solArr[LEVELSIZE]; // solution array
    int numSol = 0;
    int tp = movePos(pos, dir, 1); // move once
    for (int i = 1; i < space; i++) // for free space
    {
        if (isSolution(movePos(tp, sol[solCntr + 1], 1)))
        {
            tp = movePos(tp, dir, 1);
            printf("\tmove: %d ", tp);
        }
        else if (dir == sol[solCntr - 1] &&
                getType(movePos(tp, sol[solCntr + 1], 1) == TEX_grass))
        {
            /* just move as it is already solPath */
            return movePos(pos, dir, i);
        }
        else
        {
            /* store possible solution */
            solArr[numSol] = i;
            numSol++;
            tp = movePos(tp, dir, 1);
        }
    }
    printf("\tnumsol: %d\n", numSol);

    if (numSol)
    {
        /* pick solution */
        int r = rand() % numSol;
        printf("\trand: %d\n", r);
        /* move and place tile */
        pos = solPath(pos, dir, solArr[r]);
        if (sol[solCntr] != sol[solCntr + 1])
        {
            toTales[movePos(pos, sol[solCntr + 1], 1)].type = TEX_grass;
            printf("place ");
            printDir(sol[solCntr+1]);
            printf("\n");
        }
    }
    return pos;
}

int moveNext2(int pos, int dir, int solCntr)
{
    int space, steps, tp;

    /* check the available space in the direction */
    space = moveSpace(pos, dir);
    printf("\tFree space: %d\n", space);

    /*
     * Try to move random distance in direction
     * Temporary store possible new position in "tp"
     */
    if (space && solCntr < SOLSIZE)
    {
        steps = 1 + (rand() % space);
        printf("\tsteps: %d\n", steps);
        tp = movePos(pos, dir, steps);

        /*
         * Check if "tp" does not interfere with solution
         * path in next direction.
         */
        printf("\tcheck: ");
        printDir(sol[solCntr+1]);
        printf("\n");
        if (!isSolution(movePos(tp, sol[solCntr + 1], 1)))
        {
            /* set the tile and mark solution path */
            printf("HIT!\n");
            toTales[movePos(tp, sol[solCntr + 1], 1)].type = TEX_grass;
            printf("place ");
            printDir(sol[solCntr+1]);
            printf("\n");
            return solPath(pos, dir, steps);
        }
        else if (space > 1)
        {
            tp = bruteForce(pos, dir, space, solCntr);
            return tp;
        }
    }

    if (!isSolution(movePos(pos, sol[solCntr + 1], 1)) && (solCntr + 1) <= SOLSIZE)
    {
        printf("STAY!\n");
        toTales[movePos(pos, sol[solCntr + 1], 1)].type = TEX_grass;
        printf("place ");
        printDir(sol[solCntr+1]);
        printf("\n");
    }

    /* stay at position, don't place tile */
    return pos;
}

/* randomly set the final position 'sol[0]' */
int finalPos(int dir)
{
    /*
     * r_final: location on border for final tile/pos
     * r_move: random move distance from r_final position
     *         - possible bias
     * pos: return the position
     */
    int bias = LEVELSIZE/4;
    int r_final = 1 + (rand() % (LEVELSIZE-2));
    int r_move  = bias + (rand() % (LEVELSIZE-2 - bias));
    int pos = 0;

    /* set random location on border for final pos */
    switch (dir)
    {
        case NORTH:
            pos = r_final;
            break;
        case EAST:
            pos = (LEVELSIZE-1)+(r_final*LEVELSIZE);
            break;
        case SOUTH:
            pos = r_final+(LEVELSIZE*(LEVELSIZE-1));
            break;
        case WEST:
            pos = r_final*LEVELSIZE;
            break;
    }

    /* set the final tile */
    toTales[pos].type = TEX_water;

    /* randomly move the player in the opposite direction*/
    pos = solPath(pos, oppositeDir(dir), r_move);

    printf("%d@ ", 0);
    printDir(oppositeDir(sol[0]));
    printf("\tsteps: %d\n", r_move);

    /* put a tile for the next dir */
    if (sol[0] != sol[1])
        toTales[movePos(pos, sol[1], 1)].type = TEX_grass;

    return pos;
}

void genPath(int dir)
{
    int posID = 0;

    /* generate the solution before generating the path */
    genSol(dir);

    /* set the final position */
    posID = finalPos(sol[0]);

    for (int i = 1; i < SOLSIZE; i++)
    {
        printf("%d@ ", i);
        printDir(oppositeDir(sol[i]));
        posID = moveNext2(posID, oppositeDir(sol[i]), i);
    }
    /* set the player at the start of the path */
    Fim.pos = posID;
    Fim.moves = SOLSIZE;
}

void genLevel(void)
{
    int xpos = 0;
    int ypos = 0;
    int tileID = 0;

    /* set initialize all tiles, starting with the first column (topleft) */
    for(int c = 0; c < LEVELSIZE; c++)
    {
        /* reset xpos every loop to start at the beginning */
        xpos = 0;

        /* set the tile type and position */
        toTales[tileID].type = TEX_bg;
        toTales[tileID].xT = xpos;
        toTales[tileID].yT = ypos;
        toTales[tileID].border = true;
        /* set the border for the right column */
        if (tileID > 0)
        {
            toTales[tileID-1].border = true;
        }

        /* first tile of the row is set, move xpos once */
        xpos = TILESIZE;

        /* increase tileID for the next tile */
        if (tileID < TOTAL_TILES)
        {
            tileID += 1;
        }
        else
        {
            printf("tiles OoB\n");
        }

        /* set the tiles for the entire row */
        for(int r = 0; r < LEVELSIZE-1; r++)
        {
            /* set the tile type and position */
            toTales[tileID].type = TEX_bg;
            toTales[tileID].xT = xpos;
            toTales[tileID].yT = ypos;
            /* set the borders of the first and last row */
            if (tileID < LEVELSIZE || tileID > (TOTAL_TILES - LEVELSIZE))
            {
                toTales[tileID].border = true;
            }
            /* increase xpos since traversing through the row */
            xpos += TILESIZE;

            if (tileID < TOTAL_TILES)
            {
                tileID += 1;
            }
            else
            {
                printf("tiles OoB\n");
            }
        }
        /* row is done, increase ypos for next row */
        ypos += TILESIZE;
    }
}
