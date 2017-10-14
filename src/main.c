#include "main.h"

int main(int argc, char *argv[])
{
	int go;
	
	/* Start up SDL */
	init("Fim the game");

	/* Call the cleanup function when the program exits */
	atexit(cleanup);
	
	go = 1;
	
	/* Loop indefinitely for messages */
	while (go == 1)
	{
        printf("start");
		getInput();

        SDL_RenderClear(gRenderer);

        //Draw the image on the screen
        loadImage("gfx/sprite.png");
        //render(xpos, ypos, NULL);
        render(0, 0, gClips[TEX_sprite]);
        //render(0, 30, &gClips[TEX_grass]);
        SDL_RenderPresent(gRenderer);
		
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(16);
	}
	
	/* Exit the program */
	exit(0);
}
