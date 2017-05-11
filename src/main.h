#include "structs.h"

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

Entity fim;

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern SDL_Texture *loadImage(char *);
extern void render(int, int);
