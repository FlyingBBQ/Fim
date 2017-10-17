#include "structs.h"

struct Tiles toTales[TILES] = {{TEX_bg, 0, 0, 99, 0}};
int sol[SOLSIZE];
int colTiles[SOLSIZE];

extern int searchRow(int, int, int);
extern int searchCol(int, int, int);

extern struct Player Fim;
