#include "main.h"

int
main(void)
{
        bool alive = false;

        /* Start up SDL */
        init("Fim the game");
        /* Call the cleanup function when the program exits */
        atexit(cleanup);
        /* load the image containing all the sprites */
        loadImage("gfx/sprite.png");

        alive = true;
        while (alive) {
                getInput();

                /* Clear the screen */
                SDL_RenderClear(gRenderer);

                /* Draw the image on the screen */
                genMap(map.tiles);
                draw();

                /* Render the screen and display it */
                render(map.fim.x, map.fim.y, &gClips[TEX_sprite]);
                SDL_RenderPresent(gRenderer);

                if (Fim.moves <= 0) {
                        //alive = false;
                }
                /* Sleep briefly to stop sucking up all the CPU time */
                SDL_Delay(16);
        }
        /* Exit the program */
        exit(0);
}
