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
            if (keyState[SDL_SCANCODE_H])
            {
                Fim.prev = Fim.pos;
                while (toTales[Fim.pos-1].border != TRUE && toTales[Fim.pos-1].type != TEX_grass)
                {
                    Fim.pos -= 1;
                }
                Fim.moves -= 1;
            }
            else if (keyState[SDL_SCANCODE_J])
            {
                Fim.prev = Fim.pos;
                if ((Fim.pos + LEVELSIZE) < TILES)
                {
                    while (toTales[Fim.pos+LEVELSIZE].border != TRUE && toTales[Fim.pos+LEVELSIZE].type != TEX_grass)
                    {
                        Fim.pos += LEVELSIZE;
                    }
                    Fim.moves -= 1;
                }
            }
            else if (keyState[SDL_SCANCODE_K])
            {
                Fim.prev = Fim.pos;
                if ((Fim.pos - LEVELSIZE) > 0)
                {
                    while (toTales[Fim.pos-LEVELSIZE].border != TRUE && toTales[Fim.pos-LEVELSIZE].type != TEX_grass)
                    {
                        Fim.pos -= LEVELSIZE;
                    }
                    Fim.moves -= 1;
                }
            }
            else if (keyState[SDL_SCANCODE_L])
            {
                Fim.prev = Fim.pos;
                while (toTales[Fim.pos+1].border != TRUE && toTales[Fim.pos+1].type != TEX_grass)
                {
                    Fim.pos += 1;
                }
                Fim.moves -= 1;
            }
            else
            {
                //nothing
            }
            printf("%d\n", Fim.pos);
        }
    }
}
