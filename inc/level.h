#include "structs.h"

static const struct Tiles reset[TOTAL_TILES] = {{ 0 }};
struct Tiles toTales[TOTAL_TILES] = {{ 0 }}; // = {{TEX_bg, 0, 0, 0, 0}};
int sol[SOLSIZE];

extern int getType(int);
extern int moveSpace(int, int);
extern int movePos(int, int, int);
extern int isSolution(int);

extern struct Player Fim;
