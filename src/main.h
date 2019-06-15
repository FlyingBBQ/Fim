#include "structs.h"

SDL_Window *gWindow;
SDL_Renderer *gRenderer;
SDL_Rect gClips[MAX_SPRITES];

struct Entity texture_map;
struct Player Fim;
struct Tiles toTales[TOTAL_TILES] = {{ 0 }};

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern SDL_Texture *loadImage(char *);
extern void render(int, int, SDL_Rect *);
extern void draw(void);
