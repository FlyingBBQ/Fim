#include "main.h"

int
main(int argc, char *argv[])
{
    bool go = false;
    bool alive = false;

    /* Start up SDL */
    init("Fim the game");

    /* Call the cleanup function when the program exits */
    atexit(cleanup);

    loadImage("gfx/sprite.png");

    go = true;

    /* Loop indefinitely for messages */
    while (go) {
        /* generate the level and solutions
         * loop through all directions to test generation */
        alive = true;


        while (alive) {
            getInput();

            SDL_RenderClear(gRenderer);

            /* Draw the image on the screen */
            genMap(map.tiles);
            draw();

            render(map.fim.x, map.fim.y, &gClips[TEX_sprite]);

            SDL_RenderPresent(gRenderer);

            if (Fim.moves <= 0)
                alive = false;

            /* Sleep briefly to stop sucking up all the CPU time */
            SDL_Delay(16);
        }
    }

    /* Exit the program */
    exit(0);
}
