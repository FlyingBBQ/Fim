#include "player.h"

#include <stdbool.h>

static bool is_alive = true;
static bool quit_game = false;

void
player_init(void)
{
        is_alive = true;
}

bool
player_is_alive(void)
{
        return is_alive;
}

void
player_game_over(void)
{
        is_alive = false;
}

void
player_quit_game(void)
{
        quit_game = true;
}

bool
player_is_quitting(void)
{
        return quit_game;
}
