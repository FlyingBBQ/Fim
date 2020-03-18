#include "move.h"

#include <stdbool.h>

bool
move_position(Pos *player, Direction const dir)
{
        bool moved = false;

        switch (dir) {
        case NORTH:
                if (player->y > 0) {
                        player->y--;
                        moved = true;
                }
                break;
        case EAST:
                if (player->x < (MAP_SIZE - 1)) {
                        player->x++;
                        moved = true;
                }
                break;
        case SOUTH:
                if (player->y < (MAP_SIZE - 1)) {
                        player->y++;
                        moved = true;
                }
                break;
        case WEST:
                if (player->x > 0) {
                        player->x--;
                        moved = true;
                }
                break;
        default:
                break;
        }
        return moved;
}

void
move_position_multiple(Pos *player, Direction const dir,
                       unsigned int const steps)
{
        for (unsigned int i = 0; i < steps; ++i) {
                if (!move_position(player, dir)) {
                        break;
                }
        }
}

unsigned int
move_check_free_space(Map map, Direction const dir)
{
        unsigned int space = 0;

        while (move_position(&map.player, dir)) {
                Tiles *tile = &map.tiles[map.player.x][map.player.y];
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

        if (move_position(&map.player, dir)) {
                collision = map.tiles[map.player.x][map.player.y].flags;
        } else {
                /* if player could not move, it reached the border = dead */
                player_game_over();
        }
        return collision;
}

void
move_to_direction(Map *map, Direction const dir)
{
        unsigned int steps = move_check_free_space(*map, dir);
        move_position_multiple(&map->player, dir, steps);
}
