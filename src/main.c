#include <stdlib.h>
#include <time.h>
#include "gfx.h"
#include "input.h"
#include "level.h"

int
main(void)
{
        unsigned int levels_solved = 0;
        size_t nr_of_maps = 1;
        size_t solution_size = 8;
        size_t map_size = 16;

        // Start up SDL.
        gfx_init("Fim the game");
        // Call the cleanup function when the program exits.
        atexit(gfx_cleanup);
        // Set the random level generation seed.
        srand((unsigned int)time(NULL));

        while (!player_is_quitting()) {
                Level * level = level_new(solution_size, nr_of_maps, map_size);
                if (level == NULL) {
                        puts("Failed to create new level");
                        continue;
                } else {
                        player_init();
                        puts("=== New Level ===");
                }
                while (!level_is_finished(level)) {
                        // Get the player's input and process it in all maps.
                        input_get(level->maps, level->nr_of_maps);

                        SDL_RenderClear(gfx_get_renderer());
                        for (size_t i = 0; i < nr_of_maps; ++i) {
                                gfx_draw(level->maps[i]);
                                gfx_render_player(level->maps[i]);
                        }
                        SDL_RenderPresent(gfx_get_renderer());

                        // Sleep briefly to stop sucking up all the CPU time.
                        SDL_Delay(16);
                }
                level_clean(level);
                SDL_Delay(300);

                // Level finished, process game state for next level.
                if (player_is_alive()) {
                        levels_solved++;
                        printf("[%i] levels solved\n", levels_solved);
                        if (nr_of_maps < 4) nr_of_maps++;
                } else {
                        puts("You lost");
                        if (nr_of_maps > 1) nr_of_maps--;
                }
        }
        exit(0);
}
