#include "move.h"

#include <stdbool.h>

bool
move_position(Pos *fim, Direction const dir)
{
        bool moved = false;

        switch (dir) {
        case NORTH:
                if (fim->y > 0) {
                        fim->y--;
                        moved = true;
                }
                break;
        case EAST:
                if (fim->x < (MAP_SIZE - 1)) {
                        fim->x++;
                        moved = true;
                }
                break;
        case SOUTH:
                if (fim->y < (MAP_SIZE - 1)) {
                        fim->y++;
                        moved = true;
                }
                break;
        case WEST:
                if (fim->x > 0) {
                        fim->x--;
                        moved = true;
                }
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
