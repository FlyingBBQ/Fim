#include "player.h"

#include <stdbool.h>
#include <stdio.h>

static bool is_alive = true;
static bool quit_game = false;
static bool win = false;

void
player_init(void)
{
        is_alive = true;
        win = false;
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

void
player_win(void)
{
        puts("Win");
        win = true;
}

bool
player_has_won(void)
{
        return win;
}
