#include "level.h"

void genSol(int dir)
{
    // only call once to generate seed
    srand(time(NULL));

    // set the ending side
    sol[0] = dir;
    
    // loop through the path 
    for(int i = 1; i < SOLSIZE; i++)
    {
        // generate random number between 0-3
        int r = rand() % 4;

        // assign a random direction for the solution path
        switch(r)
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

