#include <stdbool.h>
#include "player.h"

static unsigned int lives;
static bool is_alive;

unsigned int
player_lives_left(void)
{
        return lives;
}

bool
player_is_alive(void)
{
        return is_alive;
}
