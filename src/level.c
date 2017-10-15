#include "level.h"

void genSol(int dir)
{
    // only call once to generate seed
    srand(time(NULL));

    // set the ending side
    sol[0] = dir;
    printf("sol: ");
    printf("%d", sol[0]);
    
    // loop through the path 
    for(int i = 1; i < SOLSIZE; i++)
    {
        // generate random number between 0-3
        int r = rand() % 4;

        // assign a random direction for the solution path
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

void genPath(int dir)
{
    // generate the solution before generating the path
    genSol(dir);

    // generate random number for the final tile and ID position
    int r_init = 1 + (rand() % (LEVELSIZE-2));
    int r_pos = rand() % LEVELSIZE-1;
    int posID;

    for (int i = 0; i < SOLSIZE; i++)
    {
        switch (sol[i])
        {
            case NORTH:
                // if it's the final tile
                if (i == 0) 
                {
                    // update the array of collision tiles
                    colTiles[0] = r_init; 
                    toTales[colTiles[0]].type = TEX_water;
                    // randomly move the player south to a position that can be reached with NORTH
                    posID = colTiles[0]+(r_pos*LEVELSIZE);
                }
                else
                {
                    // put a tile NORTH of last player position
                    colTiles[i] = posID-LEVELSIZE;
                    toTales[colTiles[i]].type = TEX_grass;
                    // randomly move the player south to a position that can be reached with NORTH
                    int column = (TILES-colTiles[i]) / LEVELSIZE;
                    int r = rand() % column; 
                    posID = colTiles[i]+(r*LEVELSIZE);
                }
                break;
            case EAST:
                if (i == 0) 
                {
                    colTiles[0] = (LEVELSIZE-1)+(r_init*LEVELSIZE);
                    toTales[colTiles[0]].type = TEX_water;
                    posID = colTiles[0]-r_pos;
                }
                else
                {
                    colTiles[i] = posID+1;
                    toTales[colTiles[i]].type = TEX_grass;
                    int r = rand() % (colTiles[i] % LEVELSIZE);
                    posID = colTiles[i]-r;
                }
                break;
            case SOUTH:
                if (i == 0) 
                {
                    colTiles[0] = r_init+(LEVELSIZE*(LEVELSIZE-1));
                    toTales[colTiles[0]].type = TEX_water;
                    posID = colTiles[0]-(r_pos*LEVELSIZE);
                }
                else
                {
                    colTiles[i] = posID+LEVELSIZE;
                    toTales[colTiles[i]].type = TEX_grass;
                    int r = rand() % (colTiles[i] / LEVELSIZE);
                    posID = colTiles[i]-(r*LEVELSIZE);
                }
                break;
            case WEST:
                if (i == 0) 
                {
                    colTiles[0] = r_init*LEVELSIZE;
                    toTales[colTiles[0]].type = TEX_water;
                    posID = colTiles[0]+r_pos;
                }
                else
                {
                    colTiles[i] = posID-1;
                    toTales[colTiles[i]].type = TEX_grass;
                    int r = rand() % (LEVELSIZE-(colTiles[i] % LEVELSIZE));
                    posID = colTiles[i]+r;
                }
                break;
        }
    }
    // set the player at the start of the path
    toTales[posID].type = TEX_sprite;
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

