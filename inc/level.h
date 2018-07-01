#include "structs.h"

struct Tiles toTales[TOTAL_TILES] = {{TEX_bg, 0, 0, 0, 0}};
int sol[SOLSIZE];
int colTiles[SOLSIZE];

extern int getType(int);
extern int moveSpace(int, int);
extern int movePos(int, int, int);
extern int isSolution(int);

extern struct Player Fim;
