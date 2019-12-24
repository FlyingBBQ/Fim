#include "gfx.h"
#include "input.h"

int
main(void)
{
        bool alive = false;

        /* Start up SDL */
        gfx_init("Fim the game");

        /* Call the cleanup function when the program exits */
        atexit(gfx_cleanup);

        /* create a new map */
        Map map = map_new();

        alive = true;
        while (alive) {
                input_get();

                /* Clear the screen */
                SDL_RenderClear(gfx_get_renderer());

                /* Draw the image on the screen */
                gfx_draw(&map);

                /* Render the screen and display it */
                gfx_render(map.fim.x, map.fim.y, &sprite_clips[TEX_sprite]);
                SDL_RenderPresent(gfx_get_renderer());

                /* Sleep briefly to stop sucking up all the CPU time */
                SDL_Delay(16);
        }
        /* Exit the program */
        exit(0);
}
