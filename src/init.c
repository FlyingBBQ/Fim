#include "init.h"

void
init(char *title)
{
        /* Initialise SDL Video */
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
                printf("Could not initialize SDL: %s\n", SDL_GetError());
                exit(1);
        }

        /* Open a 640 x 480 screen */
        gWindow = SDL_CreateWindow(title,
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        SCREEN_WIDTH, SCREEN_HEIGHT,
                        SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
                printf("Couldn't create window: %s\n", SDL_GetError());
                exit(1);
        }

        /* Initialize PNG loading */
        int imgFlag = IMG_INIT_PNG;
        if ( !(IMG_Init(imgFlag) & imgFlag))
        {
                printf("Couldn't initialize IMG_INIT_PNG: %s\n", IMG_GetError());
                exit(1);
        }

        /* Initialze renderer */
        int rndrFlag = SDL_RENDERER_ACCELERATED;
        gRenderer = SDL_CreateRenderer(gWindow, -1, rndrFlag);
        if (gRenderer == NULL)
        {
                printf("Window could not be rendered %s\n", SDL_GetError());
                exit(1);
        }

        SDL_SetRenderDrawColor(gRenderer, 10, 10, 10, 255);
}

void
cleanup()
{
        /* Shut down SDL */
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        gRenderer = NULL;
        gWindow = NULL;

        IMG_Quit();
        SDL_Quit();
}
