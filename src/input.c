#include "input.h"

void getInput()
{
    SDL_Event event;

    /* Loop through waiting messages and process them */

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(0);
        }

        // only check for key down states, otherwise double execution
        if (event.type == SDL_KEYDOWN)
        {
            const Uint8 *keyState = SDL_GetKeyboardState(NULL);
            if (keyState[SDL_SCANCODE_LEFT])
            {
                Fim.prev = Fim.pos;
                Fim.pos -= rowSpace(Fim.pos, WEST);
                Fim.moves -= 1;
            }
            else if (keyState[SDL_SCANCODE_DOWN])
            {
                Fim.prev = Fim.pos;
                Fim.pos += colSpace(Fim.pos, SOUTH) * LEVELSIZE;
                Fim.moves -= 1;
            }
            else if (keyState[SDL_SCANCODE_UP])
            {
                Fim.prev = Fim.pos;
                Fim.pos -= colSpace(Fim.pos, NORTH) * LEVELSIZE;
                Fim.moves -= 1;
            }
            else if (keyState[SDL_SCANCODE_RIGHT])
            {
                Fim.prev = Fim.pos;
                Fim.pos += rowSpace(Fim.pos, EAST);
                Fim.moves -= 1;
            }
            else
            {
                //nothing
            }
        }
    }
}
