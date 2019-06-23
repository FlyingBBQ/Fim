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
hasFlag(Tiles *tile, int flags)
{
        return (tile->flags & flags);
}

void
setFlag(Tiles *tile, int flags)
{
        tile->flags |= flags;
}

void
unsetFlag(Tiles *tile, int flags)
{
        tile->flags &= ~flags;
}

int
freeSpace(Map map, WAY way)
{
        int space = 0;

        while (movePos(&map.fim, way))
        {
                Tiles *tile = &map.tiles[map.fim.x][map.fim.y]; 
                if(!hasFlag(tile, (F_BORDER | F_SOLUTION)))
                {
                        space++;
                }
                else
                {
                        break;
                }
        }

        return space;
}
