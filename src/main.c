#include "main.h"

int main(int argc, char *argv[])
{
    int go = 0;
    int alive = 0;

    /* Start up SDL */
    init("Fim the game");

    /* Call the cleanup function when the program exits */
    atexit(cleanup);

    go = TRUE;

    /* Loop indefinitely for messages */
    while (go) 
    {
        // generate the level and solutions
        for (int i = 0; i < 4; i++)
        {
            genLevel();
            genPath(NORTH);

            alive = TRUE;

            while (alive)
            {
                getInput();

                SDL_RenderClear(gRenderer);

                //Draw the image on the screen
                loadImage("gfx/sprite.png");
                draw();
                render(toTales[Fim.pos].xT, toTales[Fim.pos].yT, &gClips[TEX_sprite]);
                SDL_RenderPresent(gRenderer);

                if (Fim.moves <= 0)
                {
                    alive = FALSE;
                }

                /* Sleep briefly to stop sucking up all the CPU time */
                SDL_Delay(16);
            }
        }
    }

    /* Exit the program */
    exit(0);
}
