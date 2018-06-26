#include "level.h"

int oppositeDir(int dir)
{
    if (dir == 2)
        return 4;
    else
        return (dir + 2) % 4;
}

void genSol(int dir)
{
    /* only call once to generate seed */
    srand(time(NULL));

    /* set the ending side */
    sol[0] = dir;
    printf("\nsol: ");
    printf("%d", sol[0]);

    /* loop through the path */
    for(int i = 1; i < SOLSIZE; i++)
    {
        /* generate random number between 0-3 */
        int r = rand() % 3;
        while (r == oppositeDir(sol[i-1]) ||
              (i > 1 && (r == sol[i-1] && r == sol[i-2])))
        {
            r = rand() % 3;
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
        printf("%d", sol[i]);
    }
    printf("\n");
}

/* set TILE.solution true for the solution path */
int solPath(int pos, int dir, int steps)
{
    for (int i = 0; i < steps; i++)
    {
        toTales[movePos(pos, dir, 1)].solution = true;
        toTales[movePos(pos, dir, 1)].type = TEX_sprite;
        pos = movePos(pos, dir, 1);
    }
    return pos;
}

/* calculate the next move */
int moveNext(int pos, int dir, int solCntr)
{
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

    /* put a tile for the next dir */
    if (sol[1] != sol[0])
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
        switch (sol[i])
        {
            case NORTH:
                /* check if it's not the same dir */
                if (sol[i-1] != NORTH)
                    posID = moveNext(posID, SOUTH, i);
                else if (i < SOLSIZE)
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
            case EAST:
                if (sol[i-1] != EAST)
                    posID = moveNext(posID, WEST, i);
                else if (i < SOLSIZE)
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
            case SOUTH:
                if (sol[i-1] != SOUTH)
                    posID = moveNext(posID, NORTH, i);
                else if (i < SOLSIZE)
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
            case WEST:
                if (sol[i-1] != WEST)
                    posID = moveNext(posID, EAST, i);
                else if (i < SOLSIZE)
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
        }
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
