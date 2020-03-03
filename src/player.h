#pragma once

#include <stdbool.h>

typedef struct {
        int x;
        int y;
} Pos;

unsigned int player_lives_left(void);
bool player_is_alive(void);
void player_game_over(void);
void player_init(void);

