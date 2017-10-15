#include "structs.h"

SDL_Window *gWindow;
SDL_Renderer *gRenderer;
SDL_Rect gClips[MAX_SPRITES];

struct Entity texture_map;

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern SDL_Texture *loadImage(char *);
extern void render(int, int, SDL_Rect *);
extern void draw(void);
extern void genLevel(void);
extern void genPath(int);
