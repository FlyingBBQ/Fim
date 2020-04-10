#include "input.h"

#include "move.h"

static void
input_handle_keydown(void)
{
        /* Uint8 is a type from the SDL lib */
        const Uint8 *key_state = SDL_GetKeyboardState(NULL);
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
                exit(0);
        } else {
                /* nothing */
        }

        if (0xDEAD != dir) {
                Map *map = map_get();
                move_in_direction(map, dir);
                if (move_get_collision(*map, dir) & F_FINISH) {
                        puts("win");
                        player_game_over();
                }
        }
}

void
input_get(void)
{
        SDL_Event event;

        /* Loop through waiting messages and process them */
        while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                        exit(0);
                }
                /* only check for key down states, otherwise double execution */
                if (event.type == SDL_KEYDOWN) {
                        input_handle_keydown();
                }
        }
}
