#include "structs.h"

struct Tiles toTales[TILES];
int sol[SOLSIZE];
int colTiles[SOLSIZE];

extern int searchRow(int, int, int);
extern int searchCol(int, int, int);
