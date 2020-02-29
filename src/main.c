#include "gfx.h"
#include "input.h"
#include "solver.h"

int
main(void)
{
        /* Start up SDL */
        gfx_init("Fim the game");

        /* Call the cleanup function when the program exits */
        atexit(gfx_cleanup);

        /* create a new map */
        map_new();

        Map *map = map_get();
        unsigned int const *sol = level_get_solution();

        /* move fim one step before initializing solver */
        move_position(&map->fim, move_opposite(sol[0]));
        solver_step(map, sol[0]);
        solver_sanity_check(0);

        while (player_is_alive()) {
                input_get();

                /* Clear the screen */
                SDL_RenderClear(gfx_get_renderer());

                /* Draw the image on the screen */
                gfx_draw(map);

                /* Render the screen and display it */
                gfx_render_player(map);
                SDL_RenderPresent(gfx_get_renderer());

                /* Sleep briefly to stop sucking up all the CPU time */
                SDL_Delay(16);
        }
        /* Exit the program */
        exit(0);
}
