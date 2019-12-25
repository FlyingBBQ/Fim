#include "input.h"
#include "move.h"

static void
input_handle_keydown(void)
{
        /* Uint8 is a type from the SDL lib */
        const Uint8 *key_state = SDL_GetKeyboardState(NULL);
        Map *map = map_get();

        if (key_state[SDL_SCANCODE_LEFT] || key_state[SDL_SCANCODE_A]) {
                int steps = move_check_free_space(*map, WEST);
                move_position_multiple(&map->fim, WEST, steps);
        } else if (key_state[SDL_SCANCODE_DOWN] || key_state[SDL_SCANCODE_S]) {
                int steps = move_check_free_space(*map, SOUTH);
                move_position_multiple(&map->fim, SOUTH, steps);
        } else if (key_state[SDL_SCANCODE_UP] || key_state[SDL_SCANCODE_W]) {
                int steps = move_check_free_space(*map, NORTH);
                move_position_multiple(&map->fim, NORTH, steps);
        } else if (key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_D]) {
                int steps = move_check_free_space(*map, EAST);
                move_position_multiple(&map->fim, EAST, steps);
        } else {
                /* nothing */
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
