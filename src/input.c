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
            texture_map.xpos -= TILESIZE/2;
            if(texture_map.xpos < 0) {texture_map.xpos = 0;}
        }
        else if (keyState[SDL_SCANCODE_J])
        {
            texture_map.ypos += TILESIZE/2;
            if(texture_map.ypos + texture_map.iHeight >= SCREEN_HEIGHT) 
            {
                texture_map.ypos = SCREEN_HEIGHT - texture_map.iHeight+1;
            }
        }
        else if (keyState[SDL_SCANCODE_K])
        {
            texture_map.ypos -= TILESIZE/2;
            if(texture_map.ypos < 0) {texture_map.ypos = 0;}
        }
        else if (keyState[SDL_SCANCODE_L])
        {
            texture_map.xpos += TILESIZE/2;
            if(texture_map.xpos + texture_map.iWidth >= SCREEN_WIDTH) 
            {
                texture_map.xpos = SCREEN_WIDTH - texture_map.iWidth+1;
            }
        }
        else
        {
            //nothing
        }
        SDL_Delay(1);
	}
}
