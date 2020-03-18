#include "move.h"

#include <stdbool.h>

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
move_position(Pos *fim, Direction const dir)
{
        bool moved = false;

        switch (dir) {
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
move_position_multiple(Pos *fim, Direction const dir, unsigned int const steps)
{
        for (unsigned int i = 0; i < steps; ++i) {
                if (!move_position(fim, dir)) {
                        break;
                }
        }
}

unsigned int
move_check_free_space(Map map, Direction const dir)
{
        unsigned int space = 0;

        while (move_position(&map.fim, dir)) {
                Tiles *tile = &map.tiles[map.fim.x][map.fim.y];
                if (has_flag(tile, (F_BORDER | F_FINISH))) {
                        break;
                } else {
                        space++;
                }
        }
        return space;
}

unsigned int
move_get_collision(Map map, Direction const dir)
{
        unsigned int collision = 0;

        if (move_position(&map.fim, dir)) {
                collision = map.tiles[map.fim.x][map.fim.y].flags;
        } else {
                /* if fim could not move, it reached the border = dead */
                player_game_over();
        }
        return collision;
}

void
move_to_direction(Map *map, Direction const dir)
{
        unsigned int steps = move_check_free_space(*map, dir);
        move_position_multiple(&map->fim, dir, steps);
}
