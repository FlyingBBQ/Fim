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
    // only call once to generate seed
    srand(time(NULL));

    // set the ending side
    sol[0] = dir;
    printf("\nsol: ");
    printf("%d", sol[0]);

    // loop through the path
    for(int i = 1; i < SOLSIZE; i++)
    {
        // generate random number between 1-4
        int r = 1 + rand() % 4;
        while (r == oppositeDir(sol[i-1]) || (i > 1 && (r == sol[i-1] && r == sol[i-2])))
        {
            r = 1 + rand() % 4;
        }

        // assign a random direction for the solution path
        switch (r)
        {
            case 1:
                sol[i] = NORTH;
                break;
            case 2:
                sol[i] = EAST;
                break;
            case 3:
                sol[i] = SOUTH;
                break;
            case 4:
                sol[i] = WEST;
                break;
        }
        printf("%d", sol[i]);
    }
    printf("\n");
}

int solPath(int pos, int dir, int steps)
{
    for (int i = 0; i < steps; i++)
    {
        toTales[movePos(pos, dir, 1)].solution = TRUE;
        toTales[movePos(pos, dir, 1)].type = TEX_sprite;
        pos = movePos(pos, dir, 1);
    }
    return pos;
}

int moveNext(int pos, int dir, int solCntr)
{
    int space = moveSpace(pos, dir);
    printf("space: %d\n", space);
    if (solCntr + 1 <= SOLSIZE && space > 0)
    {
        int tries = 6;
        for (int t = 0; t < tries; t++)
        {
            int steps = 1 + rand() % space;
            int tp = movePos(pos, dir, steps);
            if (!isSolution(movePos(tp, sol[solCntr + 1], 1)))
            {
                printf("solpos\n");
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

void genPath(int dir)
{
    // generate the solution before generating the path
    genSol(dir);

    // generate random number for the final tile and ID position
    int r_init = 1 + (rand() % (LEVELSIZE-2));
    int r_pos = (LEVELSIZE/4) + (rand() % (LEVELSIZE-2 - LEVELSIZE/4));
    int posID = 0;

    for (int i = 0; i < SOLSIZE; i++)
    {
        printf("%d@ ", i);
        switch (sol[i])
        {
            case NORTH:
                // if it's the final tile
                if (i == 0)
                {
                    // set the final tile
                    posID = r_init;
                    toTales[posID].type = TEX_water;
                    // randomly move the player south to a position that can be reached with NORTH
                    posID = solPath(posID, SOUTH, r_pos);
                    // put a tile for the next dir
                    if (sol[i+1] != sol[i])
                        toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                }
                // check if it's not the same dir
                else if (sol[i-1] != NORTH)
                {
                    // put a tile NORTH of last player position
                    //toTales[movePos(posID, NORTH, 1)].type = TEX_grass;
                    // randomly move the player south to a position that can be reached with NORTH
                    posID = moveNext(posID, SOUTH, i);
                        //posID = solPath(posID, SOUTH, (1 + rand() % moveSpace(posID, SOUTH)));
                        //posID = movePos(posID, SOUTH, (1 + rand() % moveSpace(posID, SOUTH)));
                }
                else
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
            case EAST:
                if (i == 0)
                {
                    posID = (LEVELSIZE-1)+(r_init*LEVELSIZE);
                    toTales[posID].type = TEX_water;
                    posID = movePos(posID, WEST, r_pos);
                    if (sol[i+1] != sol[i])
                        toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                }
                else if (sol[i-1] != EAST)
                {
                    //toTales[movePos(posID, EAST, 1)].type = TEX_grass;
                    posID = moveNext(posID, WEST, i);
                    //if (moveSpace(posID, WEST) > 0)
                    //{
                    //    posID = solPath(posID, WEST, (1 + rand() % moveSpace(posID, WEST)));
                    //}
                }
                else
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
            case SOUTH:
                if (i == 0)
                {
                    posID = r_init+(LEVELSIZE*(LEVELSIZE-1));
                    toTales[posID].type = TEX_water;
                    posID = movePos(posID, NORTH, r_pos);
                    if (sol[i+1] != sol[i])
                        toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                }
                else if (sol[i-1] != SOUTH)
                {
                    //toTales[movePos(posID, SOUTH, 1)].type = TEX_grass;
                    posID = moveNext(posID, NORTH, i);
                    //if (moveSpace(posID, NORTH) > 0)
                    //{
                    //    posID = solPath(posID, NORTH, (1 + rand() % moveSpace(posID, NORTH)));
                    //}
                }
                else
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
            case WEST:
                if (i == 0)
                {
                    posID = r_init*LEVELSIZE;
                    toTales[posID].type = TEX_water;
                    posID = movePos(posID, EAST, r_pos);
                    if (sol[i+1] != sol[i])
                        toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                }
                else if (sol[i-1] != WEST)
                {
                    //toTales[movePos(posID, WEST, 1)].type = TEX_grass;
                    posID = moveNext(posID, EAST, i);
                    //if (moveSpace(posID, EAST) > 0)
                    //{
                    //    posID = solPath(posID, EAST, (1 + rand() % moveSpace(posID, EAST)));
                    //}
                }
                else
                    toTales[movePos(posID, sol[i+1], 1)].type = TEX_grass;
                break;
        }
    }
    // set the player at the start of the path
    Fim.pos = posID;
    Fim.moves = SOLSIZE;
}

void genLevel(void)
{
    int xpos = 0;
    int ypos = 0;
    int tileID = 0;

    // set initialize all tiles, starting with the first column (topleft)
    for(int c = 0; c < LEVELSIZE; c++)
    {
        // reset xpos every loop to start at the beginning
        xpos = 0;

        // set the tile type and position
        toTales[tileID].type = TEX_bg;
        toTales[tileID].xT = xpos;
        toTales[tileID].yT = ypos;
        toTales[tileID].border = TRUE;
        // set the border for the right column
        if (tileID > 0)
        {
            toTales[tileID-1].border = TRUE;
        }

        // first tile of the row is set, move xpos once
        xpos = TILESIZE;

        // increase tileID for the next tile
        if (tileID < TILES)
        {
            tileID += 1;
        }
        else
        {
            printf("tiles OoB\n");
        }

        // set the tiles for the entire row
        for(int r = 0; r < LEVELSIZE-1; r++)
        {
            // set the tile type and position
            toTales[tileID].type = TEX_bg;
            toTales[tileID].xT = xpos;
            toTales[tileID].yT = ypos;
            // set the borders of the first and last row
            if (tileID < LEVELSIZE || tileID > (TILES - LEVELSIZE))
            {
                toTales[tileID].border = TRUE;
            }
            // increase xpos since traversing through the row
            xpos += TILESIZE;

            if (tileID < TILES)
            {
                tileID += 1;
            }
            else
            {
                printf("tiles OoB\n");
            }
        }
        // row is done, increase ypos for next row
        ypos += TILESIZE;
    }
}
