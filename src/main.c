#include <stdlib.h>
#include <time.h>
#include "gfx.h"
#include "input.h"
#include "level.h"

int
main(void)
{
        /* Start up SDL */
        gfx_init("Fim the game");

        /* Call the cleanup function when the program exits */
        atexit(gfx_cleanup);

        /* Set the random level generation seed */
        srand((unsigned int)time(NULL));

        for (;;) {
                /* Start a new level */
                player_init();

                size_t solution_size = 8;
                size_t nr_of_maps = 1;
                size_t map_size = 16;

                Level * level = level_new(solution_size, nr_of_maps, map_size);
                if (level == NULL) {
                        puts("Failed to create new level");
                        continue;
                }

                while (player_is_alive()) {
                        input_get(level->maps[0]);
                        /* Clear the screen */
                        SDL_RenderClear(gfx_get_renderer());

                        for (size_t i = 0; i < nr_of_maps; ++i) {
                                /* Draw the image on the screen */
                                gfx_draw(level->maps[i]);
                                /* Render the screen */
                                gfx_render_player(level->maps[i]);
                        }
                        /* Display the screen */
                        SDL_RenderPresent(gfx_get_renderer());
                        /* Sleep briefly to stop sucking up all the CPU time */
                        SDL_Delay(16);
                }
                level_clean(level);

                if (player_is_quitting()) {
                        break;
                }
        }
        /* Exit the program */
        exit(0);
}
