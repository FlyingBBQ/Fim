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
		const Uint8 *keyState = SDL_GetKeyboardState(NULL);
        if (keyState[SDL_SCANCODE_H])
        {
            fim.xpos -= TILESIZE;
            if(fim.xpos < 0) {fim.xpos = 0;}
        }
        else if (keyState[SDL_SCANCODE_J])
        {
            fim.ypos += TILESIZE;
            if(fim.ypos + fim.iHeight >= SCREEN_HEIGHT) 
            {
                fim.ypos = SCREEN_HEIGHT - fim.iHeight+1;
            }
        }
        else if (keyState[SDL_SCANCODE_K])
        {
            fim.ypos -= TILESIZE;
            if(fim.ypos < 0) {fim.ypos = 0;}
        }
        else if (keyState[SDL_SCANCODE_L])
        {
            fim.xpos += TILESIZE;
            if(fim.xpos + fim.iWidth >= SCREEN_WIDTH) 
            {
                fim.xpos = SCREEN_WIDTH - fim.iWidth+1;
            }
        }
        else
        {
            //nothing
        }
	}
}
