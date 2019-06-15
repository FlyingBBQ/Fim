#include "input.h"

void 
getInput()
{
    SDL_Event event;

    /* Loop through waiting messages and process them */
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        }
        /* only check for key down states, otherwise double execution */
        if (event.type == SDL_KEYDOWN) {
            const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]) {
            } 
            else if (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S]) {
            }
            else if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]) {
            }
            else if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) {
            }
            else {
                /* nothing */
            }
        }
    }
}
