#include "move.h"

static bool move_north(Pos *fim);
static bool move_east(Pos *fim);
static bool move_south(Pos *fim);
static bool move_west(Pos *fim);
static bool has_flag(Tiles *tile, unsigned char flags);

bool
move_pos(Pos *fim, WAY way)
{
        bool moved = false;

        switch (way) {
        case NORTH:
                moved = move_north(fim);
                break;
        case EAST:
                moved = move_east(fim);
                break;
        case SOUTH:
                moved = move_south(fim);
                break;
        case WEST:
                moved = move_west(fim);
                break;
        default:
                break;
        }
        return moved;
}

int
free_space(Map map, WAY way)
{
        int space = 0;

        while (move_pos(&map.fim, way)) {
                Tiles *tile = &map.tiles[map.fim.x][map.fim.y];
                if (has_flag(tile, (F_BORDER | F_SOLUTION))) {
                        break;
                } else {
                        space++;
                }
                memset(tile, 0, sizeof(Tiles));
        }
        return space;
}

void
set_flag(Tiles *tile, int flags)
{
        tile->flags |= flags;
}

void
unset_flag(Tiles *tile, int flags)
{
        tile->flags &= ~flags;
}

static bool
move_north(Pos *fim)
{
        if (fim->y > 0) {
                fim->y--;
                return true;
        }
        return false;
}

static bool
move_east(Pos *fim)
{
        if (fim->x < (MAP_SIZE - 1)) {
                fim->x++;
                return true;
        }
        return false;
}

static bool
move_south(Pos *fim)
{
        if (fim->y < (MAP_SIZE - 1)) {
                fim->y++;
                return true;
        }
        return false;
}

static bool
move_west(Pos *fim)
{
        if (fim->x > 0) {
                fim->x--;
                return true;
        }
        return false;
}

static bool
has_flag(Tiles *tile, unsigned char flags)
{
        return (tile->flags & flags);
}
