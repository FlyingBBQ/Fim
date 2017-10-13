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
		getInput();

        SDL_RenderClear(gRenderer);

        //Draw the image on the screen
        loadImage("gfx/fim.png");
        render(fim.xpos, fim.ypos);
        SDL_RenderPresent(gRenderer);
		
		/* Sleep briefly to stop sucking up all the CPU time */
		SDL_Delay(16);
	}
	
	/* Exit the program */
	exit(0);
}
