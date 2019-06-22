#include "move.h"

bool
movePos(Pos *fim, WAY way)
{
        bool res = false;

        switch (way) {
        case NORTH:
                if (fim->x > 0) {
                        fim->x--;
                        res = true;
                }
                break;
        case EAST:
                if (fim->y < MAP_SIZE) {
                        fim->y++;
                        res = true;
                }
                break;
        case SOUTH:
                if (fim->x < MAP_SIZE) {
                        fim->x++;
                        res = true;
                }
                break;
        case WEST:
                if (fim->y > 0) {
                        fim->x--;
                        res = true;
                }
                break;
        default:
                break;
        }

        return res;
}

bool
isFlag(Map *map, int flags)
{
        return (map->tiles[map->fim.x][map->fim.y].flags && flags);
}

int
freeSpace(Map map, WAY way)
{
        int space = 0;

        while (movePos(&map.fim, way)) {
                if(!isFlag(&map, F_BORDER | F_SOLUTION)) {
                        space++;
                }
                else {
                        break;
                }
        }

        return space;
}
