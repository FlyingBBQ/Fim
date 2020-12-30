#pragma once

#include <stdbool.h>

typedef struct {
        int x;
        int y;
} Pos;

void player_init(void);
bool player_is_alive(void);
void player_game_over(void);
void player_quit_game(void);
bool player_is_quitting(void);

