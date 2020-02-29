#include "move.h"

#include <stdbool.h>
#include <string.h>

Way
move_opposite(Way way)
{
        return (way + 2) % 4;
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

bool
move_position(Pos *fim, Way way)
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

void
move_position_multiple(Pos *fim, Way way, unsigned int steps)
{
        for (unsigned int i = 0; i < steps; ++i) {
                if (!move_position(fim, way)) {
                        break;
                }
        }
}

int
move_check_free_space(Map map, Way way)
{
        int space = 0;

        while (move_position(&map.fim, way)) {
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

