#include "input.h"

#include "map.h"
#include "move.h"
#include "player.h"

static void
input_handle_movement(Map ** maps, size_t const nr_of_maps, Direction const dir)
{
        for (size_t i = 0; i < nr_of_maps; ++i) {
                if (maps[i]->finished) {
                        continue;
                }
                move_in_direction(maps[i], dir);
                unsigned int collision = move_get_collision(*maps[i], dir);
                if (collision & F_BORDER) {
                        player_game_over();
                        maps[i]->finished = true;
                } else if (collision & F_FINISH) {
                        maps[i]->finished = true;
                }
        }
}

static void
input_handle_keydown(Map ** maps, size_t const nr_of_maps)
{
        // Uint8 is a type from the SDL lib.
        const Uint8 * key_state = SDL_GetKeyboardState(NULL);
        Direction dir = 0xDEAD;

        if (key_state[SDL_SCANCODE_LEFT] || key_state[SDL_SCANCODE_A]) {
                dir = WEST;
        } else if (key_state[SDL_SCANCODE_DOWN] || key_state[SDL_SCANCODE_S]) {
                dir = SOUTH;
        } else if (key_state[SDL_SCANCODE_UP] || key_state[SDL_SCANCODE_W]) {
                dir = NORTH;
        } else if (key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_D]) {
                dir = EAST;
        } else if (key_state[SDL_SCANCODE_ESCAPE]) {
                player_quit_game();
        } else {
                // Nothing.
        }

        if (dir != 0xDEAD) {
                input_handle_movement(maps, nr_of_maps, dir);
        }
}

void
input_get(Map ** maps, size_t const nr_of_maps)
{
        SDL_Event event;

        // Loop through waiting messages and process them.
        while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                        player_quit_game();
                }
                // Only check for key down states, otherwise double execution.
                if (event.type == SDL_KEYDOWN) {
                        input_handle_keydown(maps, nr_of_maps);
                }
        }
}
