#include "move.h"

bool
move_position(Map * map, Direction const dir)
{
        bool moved = false;
        int const map_size = (int)map->map_size;

        switch (dir) {
        case NORTH:
                if (map->player.y > 0) {
                        map->player.y--;
                        moved = true;
                }
                break;
        case EAST:
                if (map->player.x < (map_size - 1)) {
                        map->player.x++;
                        moved = true;
                }
                break;
        case SOUTH:
                if (map->player.y < (map_size - 1)) {
                        map->player.y++;
                        moved = true;
                }
                break;
        case WEST:
                if (map->player.x > 0) {
                        map->player.x--;
                        moved = true;
                }
                break;
        default:
                break;
        }
        return moved;
}

void
move_position_multiple(Map * map, Direction const dir,
                       unsigned int const steps)
{
        for (unsigned int i = 0; i < steps; ++i) {
                if (!move_position(map, dir)) {
                        break;
                }
        }
}

unsigned int
move_check_free_space(Map map_copy, Direction const dir)
{
        unsigned int space = 0;

        while (move_position(&map_copy, dir)) {
                Tiles * tile = &map_copy.tiles[map_copy.player.x][map_copy.player.y];
                if (has_flag(tile, (F_OBSTACLE | F_FINISH))) {
                        break;
                } else {
                        space++;
                }
        }
        return space;
}

unsigned int
move_get_collision(Map map_copy, Direction const dir)
{
        unsigned int collision = 0;

        if (move_position(&map_copy, dir)) {
                collision = map_copy.tiles[map_copy.player.x][map_copy.player.y].flags;
        } else {
                /* if player could not move, it reached the border = dead */
                player_game_over();
        }
        return collision;
}

void
move_in_direction(Map * map, Direction const dir)
{
        unsigned int steps = move_check_free_space(*map, dir);
        move_position_multiple(map, dir, steps);
}
